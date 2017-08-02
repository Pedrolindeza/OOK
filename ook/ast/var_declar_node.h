#ifndef __CDK_variableDECLARNODE_H__
#define __CDK_variableDECLARNODE_H__

#include <cdk/basic_type.h>
#include <cdk/ast/lvalue_node.h>


namespace ook {

  /**
   * Class for describing variables declaration nodes.
   */
  class var_declar_node: public cdk::basic_node {
    bool _pub, _impor;
    basic_type *_type;
    std::string *_name;

  public:
    inline var_declar_node(int lineno, bool pub, bool impor, basic_type *type, std::string *name) :
        cdk::basic_node(lineno), _pub(pub), _impor(impor), _type(type), _name(name){
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
    
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_var_declar_node(this, level);
    }

  };

} // ook

#endif