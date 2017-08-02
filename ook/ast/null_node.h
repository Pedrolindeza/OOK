#ifndef __CDK_NULLNODE_H__
#define __CDK_NULLNODE_H__

namespace ook {

  /**
   * Class for describing null_node nodes.
   */
  class null_node: public cdk::expression_node {

  public:
    inline null_node(int lineno) :
        cdk::expression_node(lineno) {
    }

  public:
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_null_node(this, level);
    }

  };

} // ook

#endif