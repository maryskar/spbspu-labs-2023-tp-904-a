#ifndef FT_COMMANDS_HPP
#define FT_COMMANDS_HPP
#include "dictionary.hpp"

namespace malaya
{
  void info(std::ostream & out);
  void deleteKey(dictOfDicts &, std::istream & in, std::ostream & out);
  void insert(dictOfDicts &, std::istream & in, std::ostream & out);
  void print(const dictOfDicts &, std::istream & in, std::ostream & out);
  void man(const descriptDict &, std::istream & in, std::ostream & out);
  void delDic(dictOfDicts &, std::istream & in, std::ostream & out);
  void search(const dictOfDicts &, std::istream & in, std::ostream & out);
  void mostFreq(const dictOfDicts &, std::istream & in, std::ostream & out);
  void areSame(const dictOfDicts & dicts, std::istream & in, std::ostream & out);
  void doSymmetricDifference(dictOfDicts & dicts, std::istream & in, std::ostream & out);
  void doSubtraction(dictOfDicts & dicts, std::istream & in, std::ostream & out);
  void isSubset(const dictOfDicts & dicts, std::istream & in, std::ostream & out);

  void merge(dictOfDicts & dicts, std::istream & in, std::ostream & out); //to do
  void getIntersection(dictOfDicts & dicts, std::istream & in, std::ostream & out);
  void input(dictOfDicts & dicts, std::istream & in, std::ostream & out); //to do
}
#endif
