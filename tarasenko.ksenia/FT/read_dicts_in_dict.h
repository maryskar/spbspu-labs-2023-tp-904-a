#ifndef FT_READ_DICTS_IN_DICT_H
#define FT_READ_DICTS_IN_DICT_H

#include <iostream>
#include <string>
#include <map>
#include <compare.h>

namespace tarasenko
{
  using dict_t = std::map< size_t, std::string, Comp >;
  void readDictsInDict(std::istream& input, std::map< std::string, dict_t, std::greater<> >& dict_of_dict);
}
#endif
