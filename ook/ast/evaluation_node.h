// $Id: evaluation_node.h,v 1.1 2017/02/17 16:02:31 david Exp $
#ifndef __OOK_EVALUATIONNODE_H__
#define __OOK_EVALUATIONNODE_H__

#include <cdk/ast/expression_node.h>

namespace ook {

  /**
   * Class for describing evaluation nodes.
   */
  class evaluation_node: public cdk::basic_node {
    cdk::expression_node *_argument;

  public:
    inline evaluation_node(int lineno, cdk::expression_node *argument) :
        cdk::basic_node(lineno), _argument(argument) {
    }

  public:
    inline cdk::expression_node *argument() {
      return _argument;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_evaluation_node(this, level);
    }

  };

} // ook

#endif
