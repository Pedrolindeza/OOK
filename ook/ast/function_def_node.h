#ifndef __CDK_FUNCTIONDEFNODE_H__
#define __CDK_FUNCTIONDEFNODE_H__

#include <cdk/basic_type.h>
#include <cdk/ast/string_node.h>
#include <cdk/ast/expression_node.h>
#include <cdk/ast/sequence_node.h>

namespace ook {

  /**
   * Class for describing if-then nodes.
   */
  class function_def_node: public cdk::basic_node {

    bool _pub;
    basic_type *_type;
    std::string *_name;
    cdk::sequence_node *_arguments;
    cdk::expression_node *_literal;
    ook::block_node *_block;
    


  public:
    inline function_def_node(int lineno, bool pub, basic_type *type, std::string *name, 
      cdk::sequence_node *arguments, cdk::expression_node *literal, ook::block_node *block) :
        cdk::basic_node(lineno), _pub(pub), _type(type), _name(name), _arguments(arguments), 
        _literal(literal), _block(block){
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
    inline cdk::sequence_node *arguments() {
      return _arguments;
    }
    inline cdk::expression_node *literal() {
      return _literal;
    }
    inline ook::block_node *block() {
      return _block;
    }
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_def_node(this, level);
    }

  };

} // xpl

#endif