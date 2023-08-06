#ifndef FT_COMMANDS_HPP
#define FT_COMMANDS_HPP
#include "dictionary.hpp"

namespace malaya
{
  void info(std::ostream & out);
  void deleteKey(dictOfDicts &, std::istream & in);
  void insert(dictOfDicts &, std::istream & in);
  void print(const dictOfDicts &, std::istream & in, std::ostream & out);
  void man(const descriptDict &, std::istream & in, std::ostream & out);
  void delDic(dictOfDicts &, std::istream & in);
  void search(const dictOfDicts &, std::istream & in, std::ostream & out);
  void mostFreq(const dictOfDicts &, std::istream & in, std::ostream & out);
  void areSame(const dictOfDicts & dicts, std::istream & in, std::ostream & out);
  void doSymmetricDifference(dictOfDicts & dicts, std::istream & in);
  void doSubtraction(dictOfDicts & dicts, std::istream & in);
  void isSubset(const dictOfDicts & dicts, std::istream & in, std::ostream & out);
  void merge(dictOfDicts & dicts, std::istream & in);
  void getIntersection(dictOfDicts & dicts, std::istream & in);
  void input(dictOfDicts & dicts, std::istream & in);
}
#endif
