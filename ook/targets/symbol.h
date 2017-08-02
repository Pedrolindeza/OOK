#ifndef __OOK_SEMANTICS_SYMBOL_H__
#define __OOK_SEMANTICS_SYMBOL_H__

#include <string>
#include <cdk/basic_type.h>

namespace ook {

    class symbol {
      basic_type *_type;
      std::string _name;
      std::vector<basic_type *> _args;
      long _value; // hack!

    public:
      inline symbol(basic_type *type, const std::string &name, long value) :
          _type(type), _name(name), _value(value) {
      }

      virtual ~symbol() {
        delete _type;
      }

      inline basic_type *type() const {
        return _type;
      }
      inline const std::string &name() const {
        return _name;
      }
      inline long value() const {
        return _value;
      }
      inline long value(long v) {
        return _value = v;
      }

      size_t arg_size() {
        return _args.size();
      }
      void add_arg(basic_type *t) {
        _args.push_back(t);
      }
      
      basic_type *get_arg(size_t i) {
        return _args.at(i);
      }

    };

} // ook

#endif
