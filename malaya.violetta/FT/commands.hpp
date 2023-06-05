#ifndef FT_COMMANDS_HPP
#define FT_COMMANDS_HPP
#include <iosfwd>
#include "helpFunctions.hpp"

namespace malaya
{
  void info(std::ostream & out);
  void deleteKey(dictOfDicts &, const std::string & first,
                 const std::string & key, std::ostream & out);
  void insert(dictOfDicts &, const std::string & first,
              const std::string & second, std::ostream & out);
  void print(dictOfDicts &, const std::string &, std::ostream & out);
  void man(const std::string & command, const descriptDict &,
           std::ostream & out);
  void delDic(dictOfDicts &, const std::string &, std::ostream & out);
  void search(dictOfDicts &, const std::string & name,
              const std::string & key, std::ostream & out);
}
#endif
