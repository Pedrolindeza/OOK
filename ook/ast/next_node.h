#ifndef __CDK_NEXTNODE_H__
#define __CDK_NEXTNODE_H__

namespace ook {

  /**
   * Class for describing next nodes.
   */
  class next_node: public cdk::basic_node {
    int _n;

  public:
    inline next_node(int lineno, int n) :
        cdk::basic_node(lineno), _n(n) {
    }

  public:
    inline int n() {
      return _n;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_next_node(this, level);
    }

  };  

} // ook

#endif