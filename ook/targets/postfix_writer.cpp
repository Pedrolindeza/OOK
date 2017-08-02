#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/postfix_writer.h"
#include "ast/all.h"  // all.h is automatically generated

//---------------------------------------------------------------------------
const ook::symbol* ooksymbol;
bool _fun;

void ook::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  if (!_fun)
    _pf.CONST(node->value()); 
  else 
    _pf.INT(node->value());
}

void ook::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
  _pf.DOUBLE(node->value()); // push a double
}

void ook::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {
  int lbl1;

  /* generate the string */
  _pf.RODATA(); // strings are DATA readonly
  _pf.ALIGN(); // make sure we are aligned
  _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
  _pf.STR(node->value()); // output string characters

  /* leave the address on the stack */
  _pf.TEXT(); // return to the TEXT segment
  _pf.ADDR(mklbl(lbl1)); // the string to be printed
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  _pf.NEG(); // 2-complement
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.ADD();
}
void ook::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.SUB();
}
void ook::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MUL();
}
void ook::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.DIV();
}
void ook::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}
void ook::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LT();
}
void ook::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LE();
}
void ook::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GE();
}
void ook::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GT();
}
void ook::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.NE();
}
void ook::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.EQ();
}
void ook::postfix_writer::do_and_node(cdk::and_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.EQ();
}
void ook::postfix_writer::do_or_node(cdk::or_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.EQ();
}
void ook::postfix_writer::do_not_node(cdk::not_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl);
  _pf.EQ();
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  // simplified generation: all variables are global
  _pf.ADDR(node->name());
}

void ook::postfix_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->lvalue()->accept(this, lvl);
  _pf.LOAD(); // depends on type size
}

void ook::postfix_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->rvalue()->accept(this, lvl); // determine the new value
  _pf.DUP();
  node->lvalue()->accept(this, lvl); // where to store the value
  _pf.STORE(); // store the value at address
}

//---------------------------------------------------------------------------

/*void ook::postfix_writer::do_program_node(ook::program_node * const node, int lvl) {
  // The ProgramNode (representing the whole program) is the
  // main function node.

  // generate the main function (RTS mandates that its name be "_main")
  _pf.TEXT();
  _pf.ALIGN();
  _pf.GLOBAL("_main", _pf.FUNC());
  _pf.LABEL("_main");
  _pf.ENTER(0);  // OOK doesn't implement local variables

  node->statements()->accept(this, lvl);

  // end the main function
  _pf.INT(0);
  _pf.POP();
  _pf.LEAVE();
  _pf.RET();

  // these are just a few library function imports
  _pf.EXTERN("readi");
  _pf.EXTERN("printi");
  _pf.EXTERN("prints");
  _pf.EXTERN("println");
  
}*/

//---------------------------------------------------------------------------

void ook::postfix_writer::do_evaluation_node(ook::evaluation_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.TRASH(4); // delete the evaluated value
  } else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.TRASH(4); // delete the evaluated value's address
  } else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
}

void ook::postfix_writer::do_print_node(ook::print_node * const node, int lvl) {

  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value to print
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.CALL("printi");
    _pf.TRASH(4); // delete the printed value
  } else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.CALL("prints");
    _pf.TRASH(4); // delete the printed value's address
  } 
  else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.CALL("printd");
    _pf.TRASH(8); // delete the printed value's address
  }
  else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
  _pf.CALL("println"); // print a newline
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_read_node(ook::read_node * const node, int lvl) {
  _pf.CALL("readi");
  _pf.PUSH();
  _pf.STORE();
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_while_node(ook::while_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1, lbl2;
  _pf.LABEL(mklbl(lbl1 = ++_lbl));
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl2 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl1));
  _pf.LABEL(mklbl(lbl2));
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_if_node(ook::if_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_if_else_node(ook::if_else_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1, lbl2;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1 = lbl2));
}

void ook::postfix_writer::do_address_of_node(ook::address_of_node * const node, int lvl){
  node->argument()->accept(this, lvl);

}

void ook::postfix_writer::do_alloc_node(ook::alloc_node * const node, int lvl){

  node->pos()->accept(this, lvl);
  _pf.INT(node->type()->subtype()->size());
  _pf.MUL();
  _pf.ALLOC();
  _pf.SP();

 }

void ook::postfix_writer::do_block_node(ook::block_node * const node, int lvl){ 

  _symtab.push();
  if (node->declaration())
    node->declaration()->accept(this, lvl+2);
  if (node->instruction())
    node->instruction()->accept(this, lvl+2);
  _symtab.pop();
}

void ook::postfix_writer::do_function_call_node(ook::function_call_node * const node, int lvl){ }

void ook::postfix_writer::do_function_def_node(ook::function_def_node * const node, int lvl){ 

  // generate the main function (RTS mandates that its name be "_main")
  if( *(node->name()) == "ook"){

    _fun=true;
    
    _pf.TEXT();
    _pf.ALIGN();
    _pf.GLOBAL("_main", _pf.FUNC());
    _pf.LABEL("_main");
    _pf.ENTER(0); 

    node->block()->accept(this, lvl);

    // end the main function
    _pf.INT(0);
    _pf.POP();
    _pf.LEAVE();
    _pf.RET();

    // these are just a few library function imports
    _pf.EXTERN("readi");
    _pf.EXTERN("printi");
    _pf.EXTERN("prints");
    _pf.EXTERN("println");

    _fun=false;
  }

  else{}

}
void ook::postfix_writer::do_var_declar_node(ook::var_declar_node * const node, int lvl){

  ASSERT_SAFE_EXPRESSIONS;
  _pf.BSS();
  _pf.ALIGN();
  _pf.GLOBAL(*(node->name()), _pf.OBJ());
  _pf.LABEL(*(node->name()));
  _pf.BYTE(node->type()->size());

}


void ook::postfix_writer::do_var_def_node(ook::var_def_node * const node, int lvl){

  ASSERT_SAFE_EXPRESSIONS;
  _pf.DATA();
  _pf.ALIGN();
  if (node->pub())
    _pf.GLOBAL(*(node->name()), _pf.OBJ());
  _pf.LABEL(*(node->name()));
  node->init()->accept(this, lvl+2);

  /*std::shared_ptr<ook::symbol> symbol = new_symbol();

  //if(_fun){

    _pf.DATA();
    _pf.ALIGN();

    if (node->pub()) 
      _pf.GLOBAL(*(node->name()), _pf.OBJ());

    _pf.LABEL(*(node->name()));
    node->init()->accept(this, lvl+2);

  } 
  else {

    node->init()->accept(this, lvl);
    if (node->type()->name() == basic_type::TYPE_DOUBLE && node->init()->type()->name() == basic_type::TYPE_INT)
      _pf.I2D();

    _pf.LOCAL(-8);
    _pf.STORE();
  }*/
  
}

void ook::postfix_writer::do_identity_node(ook::identity_node * const node, int lvl){ }
void ook::postfix_writer::do_index_node(ook::index_node * const node, int lvl){ }
void ook::postfix_writer::do_null_node(ook::null_node * const node, int lvl){ }
void ook::postfix_writer::do_return_node(ook::return_node * const node, int lvl){}
void ook::postfix_writer::do_next_node(ook::next_node * const node, int lvl){ }
void ook::postfix_writer::do_stop_node(ook::stop_node * const node, int lvl){ }
void ook::postfix_writer::do_function_declar_node(ook::function_declar_node * const node, int lvl){ }
