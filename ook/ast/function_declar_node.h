#ifndef __CDK_FUNCTIONDECLARNODE_H__
#define __CDK_FUNCTIONDECLARNODE_H__

#include <cdk/basic_type.h>
#include <cdk/ast/string_node.h>
#include <cdk/ast/sequence_node.h>

namespace ook {

  /**
   * Class for describing functions declaration nodes.
   */
  class function_declar_node: public cdk::basic_node {
    bool _pub, _impor;
    basic_type *_type;
    std::string *_name;
    cdk::sequence_node *_arguments;  //sequencia de basic nodes

  public:
    inline function_declar_node(int lineno, bool pub, bool impor, basic_type *type, std::string *name, 
      cdk::sequence_node *arguments) :
        cdk::basic_node(lineno), _pub(pub), _impor(impor), _type(type), _name(name), _arguments(arguments) {
    }

  public:
    bool pub(){
      return _pub;
    }
    bool impor(){
      return _impor;
    }
    inline basic_type *type() {
      return _type;
    }
    inline std::string *name() {
      return _name;
    }
    inline cdk::sequence_node *arguments() {
      return _arguments;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_declar_node(this, level);
    }

  };

} // ook

#endif