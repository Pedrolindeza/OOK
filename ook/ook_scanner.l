%option c++ yyclass="ook_scanner" outfile="ook_scanner.cpp"
%option stack noyywrap yylineno 8bit
%{ 
/* $Id: ook_scanner.l,v 1.6 2017/07/24 21:45:58 ist180831 Exp $ */
// make relevant includes before including the parser's tab file
#include <string>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include "ook_scanner.h"
#include "ook_parser.tab.h"

// don't change this
#define yyerror LexerError
%}
%x X_STRING X_COMMENT X_STRINGIGNORE

INT						0|([1-9][0-9]*)
DEC					    [0-9]
OCT						[0-7]

%%

">="                   return tGE; 
"<="                   return tLE; 
"=="                   return tEQ; 
"!="                   return tNE;
"!!"	 			   return tPRINTLN;	

"while"                return tWHILE; 
"if"                   return tIF; 
"else"                 return tELSE; 
"public"			   return tPUBLIC;
"import"               return tIMPORT;
"next"				   return tNEXT;	
"stop"				   return tSTOP;
"return"			   return tRETURN;	
"null"                 return tNULL;
"int"				   return tINT;
"float"                return tFLOAT;
"string"			   return tSTR;	
"pointer"			   return tPOINTER;	
"void" 				   return tVOID;	

[A-Za-z][A-Za-z0-9_]*  					yylval.s = new std::string(yytext); return tIDENTIFIER;

"//".*$                 				; /*ignorar comentarios explicativos*/

"/*"				   					yy_push_state(X_COMMENT);
<X_COMMENT>"/*"		   					yy_push_state(X_COMMENT);
<X_COMMENT>"*/"		   					yy_pop_state(); 
<X_COMMENT>.|[ \t\n\r]+  				;

\"                     					yy_push_state(X_STRING); yylval.s = new std::string("");
<X_STRING>\"           					yy_pop_state(); return tSTRING;
<X_STRING>\\0          					yy_push_state(X_STRINGIGNORE); return tSTRING;
<X_STRING>\\[0-9a-fA-F][0-9a-fA-F]? 	*yylval.s += yytext + 1;
<X_STRING>\\\'         					*yylval.s += yytext + 1;
<X_STRING>\\\"         					*yylval.s += yytext + 1;
<X_STRING>\\\\         					*yylval.s += yytext + 1;
<X_STRING>\\n	 	   					*yylval.s += "\n";
<X_STRING>\\r	 	   					*yylval.s += "\r";
<X_STRING>\\t	 	   					*yylval.s += "\t";
<X_STRING>\n           					yyerror("newline in string");
<X_STRING>.            					*yylval.s += yytext;

<X_STRINGIGNORE>\"	   					yy_pop_state(); yy_pop_state();
<X_STRINGIGNORE>\n     					yyerror("newline in string");
<X_STRINGIGNORE>.	   					;	

{INT}  				                	{	try { yylval.i = strtol(yytext, nullptr, 10);
												  return tINTEGER;}
									   		catch (std::out_of_range){
												yyerror("Int Overflow");} }	
0{OCT}+								   	{	try { yylval.i = strtol(yytext, nullptr, 8);
												  return tINTEGER;}
											catch (std::out_of_range){
												yyerror("Int Overflow");} }	

[0-9]+\.[0-9]+([Ee][+-]?[0-9]+)?		yylval.d = std::stod(yytext); return tDOUBLE; //retirado da wiki
[0-9]*\.[0-9]+([Ee][+-]?[0-9]+)?		yylval.d = std::stod(yytext); return tDOUBLE;
[0-9]+([Ee][+-]?[0-9]+)					yylval.d = std::stod(yytext); return tDOUBLE;


[-()<>=+*,&&\[\]|?!/~|\?!/~@%;{}.]       return *yytext;

[ \t\n\r]+             					; /* ignore whitespace */

.                      					yyerror("Unknown character");

%%
// Very, very dirty hack: flex is a mess generating C++ scanners.
int ook_scanner::yywrap() { return 1; }
