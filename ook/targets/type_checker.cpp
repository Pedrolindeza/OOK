#include <string>
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }

//---------------------------------------------------------------------------
const ook::symbol* symbol;

void ook::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void ook::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_STRING));
}

void ook::type_checker::do_double_node(cdk::double_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

//---------------------------------------------------------------------------

inline void ook::type_checker::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in argument of unary expression");

  // in OOK, expressions are always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void ook::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

inline void ook::type_checker::processBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in right argument of binary expression");

  // in OOK, expressions are always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void ook::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_mod_node(cdk::mod_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_and_node(cdk::and_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_or_node(cdk::or_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_not_node(cdk::not_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void ook::type_checker::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  
  ASSERT_UNSPEC;

  const std::string &id = node->name();
  std::shared_ptr<ook::symbol> symbol = _symtab.find(id);

  if (symbol != nullptr) {
    node->type(symbol->type());
  }
  else {
    throw id;
  }
}

void ook::type_checker::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_UNSPEC;
  try {
    node->lvalue()->accept(this, lvl);
    node->type(node->lvalue()->type());
  } catch (const std::string &id) {
    throw "undeclared variable '" + id + "'";
  }
}

void ook::type_checker::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_UNSPEC;
  
  node->lvalue()->accept(this, lvl);
  if (node->lvalue()->type()->name() != basic_type::TYPE_INT && 
      node->lvalue()->type()->name() != basic_type::TYPE_STRING && 
      node->lvalue()->type()->name() != basic_type::TYPE_DOUBLE && 
      node->lvalue()->type()->name() != basic_type::TYPE_POINTER)
    throw std::string("wrong type in left argument of assignment expression");

  node->rvalue()->accept(this, lvl);
  if (node->lvalue()->type()->name() == basic_type::TYPE_POINTER && 
      node->rvalue()->type()->name() == basic_type::TYPE_POINTER) {
        node->type(node->lvalue()->type());
        node->rvalue()->type(node->lvalue()->type());
  } 
  else if (node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE && 
           node->rvalue()->type()->name() == basic_type::TYPE_INT)
    node->type(node->lvalue()->type());
  else if (node->lvalue()->type()->name() == node->rvalue()->type()->name())
    node->type(node->lvalue()->type());
  else if (node->rvalue()->type()->name() == basic_type::TYPE_UNSPEC)
    node->type(node->lvalue()->type());
  else
    throw std::string("wrong type in right argument of assignment expression");
}

//---------------------------------------------------------------------------

void ook::type_checker::do_evaluation_node(ook::evaluation_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

void ook::type_checker::do_print_node(ook::print_node * const node, int lvl) {

  node->argument()->accept(this, lvl + 2);

  if (node->argument()->type()->name() == basic_type::TYPE_UNSPEC)
    node->argument()->type(new basic_type(4, basic_type::TYPE_INT));
}

//---------------------------------------------------------------------------

void ook::type_checker::do_read_node(ook::read_node * const node, int lvl) {

  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_UNSPEC));

}

//---------------------------------------------------------------------------

void ook::type_checker::do_while_node(ook::while_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

//---------------------------------------------------------------------------

void ook::type_checker::do_if_node(ook::if_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

void ook::type_checker::do_if_else_node(ook::if_else_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

void ook::type_checker::do_address_of_node(ook::address_of_node * const node, int lvl){ 

  node->lvalue()->accept(this, lvl);
  node->type(new basic_type(4, basic_type::TYPE_POINTER));
  node->type()->_subtype = node->lvalue()->type();

}

void ook::type_checker::do_alloc_node(ook::alloc_node * const node, int lvl){ 

  node->pos()->accept(this, lvl);

  if (node->pos()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in positions");

  node->type(new basic_type(4, basic_type::TYPE_POINTER));

  node->type()->_subtype = new basic_type(4, basic_type::TYPE_UNSPEC);

}

void ook::type_checker::do_index_node(ook::index_node * const node, int lvl){

  node->base()->accept(this, lvl);
  if (node->base()->type()->name() != basic_type::TYPE_POINTER)
    throw std::string("wrong type in base");
  
  node->offset()->accept(this, lvl);
  if (node->offset()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in offset");

  node->type(node->base()->type()->subtype());

 }
void ook::type_checker::do_function_call_node(ook::function_call_node * const node, int lvl){ 

  const std::string &id = "function " + *(node->name());
  std::shared_ptr<symbol> symbol = _symtab.find(id);

  if (symbol == nullptr) 
    throw id + " undeclared";
  else
    node->type(new basic_type(*symbol->type()));
}

void ook::type_checker::do_function_declar_node(ook::function_declar_node * const node, int lvl){
   
   const std::string &id = "function " + *(node->name());
  
  std::shared_ptr<symbol> fun = std::make_shared<symbol>(new basic_type(*node->type()), id, 0);
  _symtab.insert(id, fun);

  if (node->arguments()) {

    int aux = node->arguments()->size();
    int i=0;

    while(i<aux) {

      ook::var_declar_node *arg = (ook::var_declar_node*) (node->arguments()->node(i));
      fun->add_arg(new basic_type(*arg->type()));
      i++;

    } 
  }

}

void ook::type_checker::do_function_def_node(ook::function_def_node * const node, int lvl){
  
  
  const std::string &id = "function " + *(node->name());
  
  std::shared_ptr<symbol> fun = _symtab.find(id);

  if(fun == nullptr)
    fun = std::make_shared<symbol>(new basic_type(*node->type()), id, 0);
  
  _symtab.insert(id, fun);

  if (node->arguments()) {

    int aux = node->arguments()->size();
    int i=0;

    while(i<aux) {

      ook::var_declar_node *arg = (ook::var_declar_node*) (node->arguments()->node(i));
      fun->add_arg(new basic_type(*arg->type()));
      i++;

    }
  }  
}

void ook::type_checker::do_var_declar_node(ook::var_declar_node * const node, int lvl){
  
  std::string &id = *(node->name());
  _symtab.insert(id, std::make_shared<symbol>(new basic_type(*node->type()), id, 0));  

}

void ook::type_checker::do_var_def_node(ook::var_def_node * const node, int lvl){ 

  std::string &id = *(node->name());
  std::shared_ptr<symbol> ref = std::make_shared<symbol>(new basic_type(*node->type()), id, 0);
   _symtab.insert(id,ref);
   _parent->set_new_symbol(ref);

  node->init()->accept(this, lvl+2);
  if (node->init()->type()->name()==basic_type::TYPE_UNSPEC)
    node->init()->type(node->type());

  if (node->type()->name() == basic_type::TYPE_POINTER && node->init()->type()->name() == basic_type::TYPE_INT)
    node->init()->type(node->type());

}

void ook::type_checker::do_identity_node(ook::identity_node * const node, int lvl){ 
  processUnaryExpression(node, lvl);
}

void ook::type_checker::do_block_node(ook::block_node * const node, int lvl){
   if (node->declaration())
    node->declaration()->accept(this, lvl+2);
  if (node->instruction())
    node->instruction()->accept(this, lvl+2);

}


/*EMPTY*/
void ook::type_checker::do_stop_node(ook::stop_node * const node, int lvl){}
void ook::type_checker::do_next_node(ook::next_node * const node, int lvl){}
void ook::type_checker::do_null_node(ook::null_node * const node, int lvl){ }
void ook::type_checker::do_return_node(ook::return_node * const node, int lvl){ }
