#ifndef FT_COMMANDS_HPP
#define FT_COMMANDS_HPP
#include "helpFunctions.hpp"

namespace malaya
{
  void info(std::ostream & out);
  void deleteKey(dictOfDicts &, std::istream & in, std::ostream & out);
  void insert(dictOfDicts &, std::istream & in, std::ostream & out);
  void print(dictOfDicts &, std::istream & in, std::ostream & out);
  void man(const descriptDict &, std::istream & in, std::ostream & out);
  void delDic(dictOfDicts &, std::istream & in, std::ostream & out);
  void search(dictOfDicts &, std::istream & in, std::ostream & out);
  void mostFreq(dictOfDicts &, std::istream & in, std::ostream & out);
  void areSame(dictOfDicts & dicts, std::istream & in, std::ostream & out);
  void doSymmetricDifference(dictOfDicts & dicts, std::istream & in, std::ostream & out);
  void doSubtraction(dictOfDicts & dicts, std::istream & in, std::ostream & out);
}
#endif
