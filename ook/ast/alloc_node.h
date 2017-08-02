#ifndef __CDK_ALLOCNODE_H__
#define __CDK_ALLOCNODE_H__

#include <cdk/basic_type.h>
#include <cdk/ast/string_node.h>
#include <cdk/ast/expression_node.h>

namespace ook {

  /**
   * Class for describing if-then nodes.
   */
  class alloc_node: public cdk::unary_expression_node {
    cdk::expression_node *_pos;

  public:
    inline alloc_node(int lineno, cdk::expression_node *pos) :
        cdk::unary_expression_node(lineno, pos), _pos(pos) {
    }

  public:
    inline cdk::expression_node *pos() {
      return _pos;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_alloc_node(this, level);
    }

  };

} // ook

#endif 
