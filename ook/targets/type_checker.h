// $Id: type_checker.h,v 1.3 2017/07/14 18:24:45 ist180831 Exp $ -*- c++ -*-
#ifndef __OOK_SEMANTICS_TYPE_CHECKER_H__
#define __OOK_SEMANTICS_TYPE_CHECKER_H__

#include <string>
#include <iostream>
#include <cdk/symbol_table.h>
#include <cdk/ast/basic_node.h>
#include "targets/symbol.h"
#include "targets/basic_ast_visitor.h"

namespace ook {

  /**
   * Print nodes as XML elements to the output stream.
   */
  class type_checker: public basic_ast_visitor {
    cdk::symbol_table<ook::symbol> &_symtab;

    basic_ast_visitor *_parent;

  public:
    type_checker(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<ook::symbol> &symtab, basic_ast_visitor *parent) :
        basic_ast_visitor(compiler), _symtab(symtab), _parent(parent) {
    }

  public:
    ~type_checker() {
      os().flush();
    }

  public:
    void do_sequence_node(cdk::sequence_node * const node, int lvl) {
    }

  protected:
    template<typename T>
    void process_literal(cdk::literal_node<T> * const node, int lvl) {
    }

  public:
    void do_integer_node(cdk::integer_node * const node, int lvl);
    void do_string_node(cdk::string_node * const node, int lvl);

  protected:
    void processUnaryExpression(cdk::unary_expression_node * const node, int lvl);

  public:
    void do_neg_node(cdk::neg_node * const node, int lvl);

  protected:
    void processBinaryExpression(cdk::binary_expression_node * const node, int lvl);

  public:
    void do_add_node(cdk::add_node * const node, int lvl);
    void do_sub_node(cdk::sub_node * const node, int lvl);
    void do_mul_node(cdk::mul_node * const node, int lvl);
    void do_div_node(cdk::div_node * const node, int lvl);
    void do_mod_node(cdk::mod_node * const node, int lvl);
    void do_lt_node(cdk::lt_node * const node, int lvl);
    void do_le_node(cdk::le_node * const node, int lvl);
    void do_ge_node(cdk::ge_node * const node, int lvl);
    void do_gt_node(cdk::gt_node * const node, int lvl);
    void do_ne_node(cdk::ne_node * const node, int lvl);
    void do_eq_node(cdk::eq_node * const node, int lvl);
    void do_and_node(cdk::and_node * const node, int lvl);
    void do_or_node(cdk::or_node * const node, int lvl);
    void do_not_node(cdk::not_node * const node, int lvl);
    void do_double_node(cdk::double_node * const node, int lvl);
    
  public:
    void do_identifier_node(cdk::identifier_node * const node, int lvl);
    void do_rvalue_node(cdk::rvalue_node * const node, int lvl);
    void do_assignment_node(cdk::assignment_node * const node, int lvl);

  public:
    /*void do_program_node(ook::program_node * const node, int lvl) {
    }*/
    void do_evaluation_node(ook::evaluation_node * const node, int lvl);
    void do_print_node(ook::print_node * const node, int lvl);
    void do_read_node(ook::read_node * const node, int lvl);

  public:
    void do_while_node(ook::while_node * const node, int lvl);
    void do_if_node(ook::if_node * const node, int lvl);
    void do_if_else_node(ook::if_else_node * const node, int lvl);

  public:
    void do_address_of_node(ook::address_of_node * const node, int lvl);
    void do_alloc_node(ook::alloc_node * const node, int lvl);
    void do_block_node(ook::block_node * const node, int lvl);
    void do_function_call_node(ook::function_call_node * const node, int lvl);
    void do_function_declar_node(ook::function_declar_node * const node, int lvl);
    void do_function_def_node(ook::function_def_node * const node, int lvl);
    void do_identity_node(ook::identity_node * const node, int lvl);
    void do_index_node(ook::index_node * const node, int lvl);
    void do_next_node(ook::next_node * const node, int lvl);
    void do_null_node(ook::null_node * const node, int lvl);
    void do_return_node(ook::return_node * const node, int lvl);
    void do_stop_node(ook::stop_node * const node, int lvl);
    void do_var_declar_node(ook::var_declar_node * const node, int lvl);
    void do_var_def_node(ook::var_def_node * const node, int lvl);    
  };

} // ook

//---------------------------------------------------------------------------
//     HELPER MACRO FOR TYPE CHECKING
//---------------------------------------------------------------------------

#define CHECK_TYPES(compiler, symtab, node) { \
  try { \
    ook::type_checker checker(compiler, symtab, this); \
    (node)->accept(&checker, 0); \
  } \
  catch (const std::string &problem) { \
    std::cerr << (node)->lineno() << ": " << problem << std::endl; \
    return; \
  } \
}

#define ASSERT_SAFE_EXPRESSIONS CHECK_TYPES(_compiler, _symtab, node)

#endif
