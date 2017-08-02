#ifndef __CDK_VARDEFNODE_H__
#define __CDK_VARDEFNODE_H__

#include <cdk/basic_type.h>
#include <cdk/ast/lvalue_node.h>
#include <cdk/ast/expression_node.h>

namespace ook {

  /**
   * Class for describing variables definition nodes.
   */
  class var_def_node: public cdk::basic_node {
    bool _pub;
    basic_type *_type;
    std::string *_name;
    cdk::expression_node *_init;

  public:
    inline var_def_node(int lineno, bool pub, basic_type *type, std::string *name, cdk::expression_node *init) :
        cdk::basic_node(lineno), _pub(pub), _type(type), _name(name), _init(init) {
    }

  public:
    bool pub(){
      return _pub;
    }

    inline basic_type *type() {
      return _type;
    }

    inline std::string *name() {
      return _name;
    }

    inline cdk::expression_node *init() {
      return _init;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_var_def_node(this, level);
    }

  };

} // ook

#endif