%{
// $Id: ook_parser.y,v 1.7 2017/07/24 21:45:58 ist180831 Exp $
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!
%}

%union {
  int                   i;	/* integer value */
  double                d;  /*double value*/
  std::string          *s;	/* symbol name or string literal */
  bool                 boolean;
  cdk::basic_node      *node;	/* node pointer */
  basic_type           *type; 
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  cdk::lvalue_node     *lvalue;
  ook::block_node      *blocky;
};

%token <i> tINTEGER
%token <d> tDOUBLE
%token <s> tIDENTIFIER tSTRING
%token tWHILE tIF tPUBLIC tIMPORT tNEXT tSTOP tRETURN tNULL tINT tFLOAT tSTR tPOINTER tVOID tPRINTLN
%nonassoc tIFX
%nonassoc tELSE

%right '='
%left tGE tLE tEQ tNE '>' '<'
%left '+' '-' '&' '|' 
%left '*' '/' '%'
%nonassoc '[' '~' tUNARY 

%type <node> stmt program var block_var function declar block_declar iteration condition arg
%type <sequence> list file declars args2 args block_declars exprs
%type <expression> expr literal
%type <s> string
%type <lvalue> lval
%type <type> type
%type <blocky> block

%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

program : file                           { compiler->ast($1); }
        ;

file : declar                            { $$ = new cdk::sequence_node(LINE, $1); }
     | declars declar                    { $$ = new cdk::sequence_node(LINE, $2, $1); }
     | /*empty*/                         { $$ = nullptr; }
     ;

list : stmt                              { $$ = new cdk::sequence_node(LINE, $1); }
     | list stmt                         { $$ = new cdk::sequence_node(LINE, $2, $1); }
     ;

stmt : expr ';'                          { $$ = new ook::evaluation_node(LINE, $1); }
     | expr '!'                          { $$ = new ook::print_node(LINE, $1);}
     | expr tPRINTLN                     { $$ = new ook::print_node(LINE, $1);}
     | tSTOP ';'                         { $$ = new ook::stop_node(LINE, 1);}
     | tSTOP tINTEGER ';'                { $$ = new ook::stop_node(LINE, $2);}
     | tNEXT ';'                         { $$ = new ook::next_node(LINE, 1);}
     | tNEXT tINTEGER ';'                { $$ = new ook::next_node(LINE, $2);}
     | tRETURN                           { $$ = new ook::return_node(LINE);}
     | condition                         { $$ = $1;}
     | iteration                         { $$ = $1;}
     | block                             { $$ = $1;}
     ;

expr : '-' expr %prec tUNARY             { $$ = new cdk::neg_node(LINE, $2); }  
     | expr '+' expr                     { $$ = new cdk::add_node(LINE, $1, $3); }
     | expr '-' expr                     { $$ = new cdk::sub_node(LINE, $1, $3); }
     | expr '*' expr                     { $$ = new cdk::mul_node(LINE, $1, $3); }
     | expr '/' expr                     { $$ = new cdk::div_node(LINE, $1, $3); }
     | expr '%' expr                     { $$ = new cdk::mod_node(LINE, $1, $3); }
     | expr '<' expr                     { $$ = new cdk::lt_node(LINE, $1, $3); }
     | expr '>' expr                     { $$ = new cdk::gt_node(LINE, $1, $3); }
     | expr tGE expr                     { $$ = new cdk::ge_node(LINE, $1, $3); }
     | expr tLE expr                     { $$ = new cdk::le_node(LINE, $1, $3); }
     | expr tNE expr                     { $$ = new cdk::ne_node(LINE, $1, $3); }
     | expr tEQ expr                     { $$ = new cdk::eq_node(LINE, $1, $3); }
     | '(' expr ')'                      { $$ = $2; }
     | lval                              { $$ = new cdk::rvalue_node(LINE, $1); }
     | lval '=' expr                     { $$ = new cdk::assignment_node(LINE, $1, $3); }
     | '+' expr %prec tUNARY             { $$ = new ook::identity_node(LINE, $2); }
     | expr '&' expr                     { $$ = new cdk::and_node(LINE, $1, $3); }
     | expr '|' expr                     { $$ = new cdk::or_node(LINE, $1, $3); }
     | '~' expr                          { $$ = new cdk::not_node(LINE, $2); }
     | '[' expr ']'                      { $$ = new ook::alloc_node(LINE, $2); }
     | lval '?'                          { $$ = new ook::address_of_node(LINE, $1); }
     | '@'                               { $$ = new ook::read_node(LINE); }
     | literal                           { $$ = $1;}
     | tIDENTIFIER '(' exprs ')'         { $$ = new ook::function_call_node(LINE, $1, $3);}
     | tIDENTIFIER '(' ')'               { $$ = new ook::function_call_node(LINE, $1, new cdk::sequence_node(LINE)); }
     ;

lval : tIDENTIFIER                       { $$ = new cdk::identifier_node(LINE, $1); }
     | expr '[' expr ']'                 { $$ = new ook::index_node(LINE, $1, $3); }
     ;

type : tINT                              { $$ = new basic_type(4, basic_type::TYPE_INT);}
     | tFLOAT                            { $$ = new basic_type(8, basic_type::TYPE_DOUBLE);}
     | tSTR                              { $$ = new basic_type(4, basic_type::TYPE_STRING);} 
     | tPOINTER                          { $$ = new basic_type(4, basic_type::TYPE_POINTER);}
     ;

literal : tNULL                          { $$ = new ook::null_node(LINE); };
        | tINTEGER                       { $$ = new cdk::integer_node(LINE, $1); }
        | string                         { $$ = new cdk::string_node(LINE,  $1); }
        | tDOUBLE                        { $$ = new cdk::double_node(LINE, $1); } 
        ;

string : tSTRING                         { $$ = $1;} 
       | string tSTRING                  { *$$ = *$1 + *$2; }
       ;

declar : var ';'                         { $$ = $1; }
       | function                        { $$ = $1;}
       ;

block_declar : block_var ';'             { $$ = $1;}
             ; 

block_var : type tIDENTIFIER                    { $$ = new ook::var_declar_node(LINE, false, false, $1, $2);}
          | type tIDENTIFIER '=' expr           { $$ = new ook::var_def_node(LINE, false, $1, $2, $4);}
          ;

declars  : declar                               { $$ = new cdk::sequence_node(LINE, $1); }
         | declars declar                       { $$ = new cdk::sequence_node(LINE, $2, $1); }
         ;

block_declars : block_declar                    { $$ = new cdk::sequence_node(LINE, $1); }
              | block_declars block_declar      { $$ = new cdk::sequence_node(LINE, $2, $1); }
              ;

var : tPUBLIC type tIDENTIFIER                  { $$ = new ook::var_declar_node(LINE, true, false, $2, $3);}
    | tIMPORT type tIDENTIFIER                  { $$ = new ook::var_declar_node(LINE, false, true, $2, $3);}
    | tPUBLIC type tIDENTIFIER '=' expr         { $$ = new ook::var_def_node(LINE, true, $2, $3, $5);}
    | block_var                                 { $$ = $1;} 
    ;

arg : type tIDENTIFIER                          { $$ = new ook::var_declar_node(LINE, false, false, $1, $2);}
    ;

args : args2                                    { $$ = $1;}
     | /*empty*/                                { $$ = nullptr;}
     ;

args2 : arg                                     { $$ = new cdk::sequence_node(LINE, $1);}
      | args2 ',' arg                           { $$ = new cdk::sequence_node(LINE, $3, $1);}    
      ;

block : '{' block_declars list '}'              { $$ = new ook::block_node(LINE, $2, $3);}
      | '{' block_declars '}'                   { $$ = new ook::block_node(LINE, $2, new cdk::sequence_node(LINE));} 
      | '{' list '}'                            { $$ = new ook::block_node(LINE, new cdk::sequence_node(LINE), $2);} 
      | '{' '}'                                 { $$ = new ook::block_node(LINE, new cdk::sequence_node(LINE), new cdk::sequence_node(LINE));} 
      ;

iteration  : tWHILE '(' expr ')' stmt           { $$ = new ook::while_node(LINE, $3, $5);}       
           ; 

exprs      : expr                               { $$ = new cdk::sequence_node(LINE, $1);}
           | exprs ',' expr                     { $$ = new cdk::sequence_node(LINE, $3, $1);}
           ;

condition  : tIF '(' expr ')' stmt %prec tIFX   { $$ = new ook::if_node(LINE, $3, $5);}
           | tIF '(' expr ')' stmt tELSE stmt   { $$ = new ook::if_else_node(LINE, $3, $5, $7);}
           ;

function : tPUBLIC type tIDENTIFIER '(' args ')'    
            {$$ = new ook::function_declar_node(LINE, true, false, $2, $3, $5);}
         | tPUBLIC tVOID tIDENTIFIER '(' args ')'    
            {$$ = new ook::function_declar_node(LINE, true, false, new basic_type(0, basic_type::TYPE_VOID), $3, $5);}
         | tIMPORT type tIDENTIFIER '(' args ')'
            {$$ = new ook::function_declar_node(LINE, false, true, $2, $3, $5);}
         | tIMPORT tVOID tIDENTIFIER '(' args ')'
            {$$ = new ook::function_declar_node(LINE, false, true, new basic_type(0, basic_type::TYPE_VOID), $3, $5);}
         | type tIDENTIFIER '(' args ')'
            {$$ = new ook::function_declar_node(LINE, false, false, $1, $2, $4);}
         | tVOID tIDENTIFIER '(' args ')'
            {$$ = new ook::function_declar_node(LINE, false, false, new basic_type(0, basic_type::TYPE_VOID), $2, $4);}
         | tPUBLIC type tIDENTIFIER '(' args ')' '=' literal block
            {$$ = new ook::function_def_node(LINE, true, $2, $3, $5, $8, $9);}
         | tPUBLIC type tIDENTIFIER '(' args ')' block
            {$$ = new ook::function_def_node(LINE, true, $2, $3, $5, nullptr, $7);}
         | type tIDENTIFIER '(' args ')' '=' literal block
            {$$ = new ook::function_def_node(LINE, false, $1, $2, $4, $7, $8);}
         | type tIDENTIFIER '(' args ')' block
            {$$ = new ook::function_def_node(LINE, false, $1, $2, $4, nullptr, $6);}
         | tPUBLIC tVOID tIDENTIFIER '(' args ')' block
            {$$ = new ook::function_def_node(LINE, true, new basic_type(0, basic_type::TYPE_VOID), $3, $5, nullptr, $7);}
         | tVOID tIDENTIFIER '(' args ')' block
            {$$ = new ook::function_def_node(LINE, false, new basic_type(0, basic_type::TYPE_VOID), $2, $4, nullptr, $6);}     
         ;    
%%
