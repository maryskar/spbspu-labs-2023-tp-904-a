#ifndef IOTYPES_H
#define IOTYPES_H
#include <complex>

namespace samoilenko
{
  struct Delimiter
  {
    char exp;
  };
  struct BinUll
  {
    unsigned long long& n;
  };
  struct ComplexNum
  {
    std::complex< double >& cmpNum;
  };
  struct String
  {
    std::string& str;
  };
  struct Label
  {
    std::string exp;
  };
  std::istream& operator>>(std::istream& in, Delimiter&& dest);
  std::istream& operator>>(std::istream& in, BinUll&& dest);
  std::istream& operator>>(std::istream& in, ComplexNum&& dest);
  std::istream& operator>>(std::istream& in, String&& dest);
  std::istream& operator>>(std::istream& in, Label&& dest);
}

#endif
