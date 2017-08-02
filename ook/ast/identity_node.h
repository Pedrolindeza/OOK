#ifndef __CDK_IDENTITYNODE_H__
#define __CDK_IDENTITYNODE_H__

namespace ook {

  /**
   * Class for describing the identity operator
   */
  class identity_node: public cdk::unary_expression_node {

  public:
    inline identity_node(int lineno, cdk::expression_node *arg) :
        cdk::unary_expression_node(lineno, arg) {
    }

  public:
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_identity_node(this, level);
    }

  };

} // ook

#endif 
