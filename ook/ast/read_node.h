// $Id: read_node.h,v 1.2 2017/07/03 01:24:09 ist180831 Exp $ -*- c++ -*-
#ifndef __OOK_READNODE_H__
#define __OOK_READNODE_H__

namespace ook {

  /**
   * Class for describing read nodes.
   */
  class read_node: public cdk::expression_node {
    

  public:
    inline read_node(int lineno) :
        cdk::expression_node(lineno) {
    }

  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_read_node(this, level);
    }

  };

} // ook

#endif
