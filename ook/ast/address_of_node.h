#ifndef __CDK_ADDRESSOFNODE_H__
#define __CDK_ADDRESSOFNODE_H__

#include <cdk/ast/lvalue_node.h>

namespace ook {

  /**
   * Class for describing address_of nodes.
   */
  class address_of_node: public cdk::unary_expression_node {
    cdk::lvalue_node *_lvalue;

  public:
    inline address_of_node(int lineno, cdk::lvalue_node *lvalue) :
        cdk::unary_expression_node(lineno,lvalue), _lvalue(lvalue){
    }

  public:
    inline cdk::lvalue_node *lvalue() {
      return _lvalue;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_address_of_node(this, level);
    }

  };

} // ook

#endif