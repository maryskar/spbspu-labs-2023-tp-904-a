#ifndef SPBSPU_LABS_2023_TP_904_AM_TYPESIO_H
#define SPBSPU_LABS_2023_TP_904_AM_TYPESIO_H
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
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
  struct CmpLspI
  {
    std::complex< double >& ref;
  };
  struct StringIO
  {
    std::string& str;
  };
  struct CmpLspO
  {
    std::complex< double > ref;
  };
  std::istream& operator>>(std::istream& in, DelIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, CharLitIO&& dest);
  std::istream& operator>>(std::istream& in, CmpLspI&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::ostream& operator<<(std::ostream& out, const CmpLspO& dest);
}
#endif
