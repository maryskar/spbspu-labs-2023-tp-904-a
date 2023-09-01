#ifndef SPBSPU_LABS_2023_TP_904_AM_TYPESIO_H
#define SPBSPU_LABS_2023_TP_904_AM_TYPESIO_H
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <sstream>
#include "data_struct.h"

namespace shestakov
{
  struct DelIO
  {
    char exp;
  };
  struct LabelIO
  {
    std::string str;
  };
  struct CharLitIO
  {
    char& ref;
  };
  struct CmpLspIO
  {
    std::complex< double >& ref;
  };
  struct StringIO
  {
    std::string& str;
  };
  std::istream& operator>>(std::istream& in, DelIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, CharLitIO&& dest);
  std::istream& operator>>(std::istream& in, CmpLspIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif
