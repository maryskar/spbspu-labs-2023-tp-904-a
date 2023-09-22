#ifndef IOTYPES_H
#define IOTYPES_H
#include <complex>

namespace samoilenko
{
  struct Delimiter
  {
    char exp;
  };
  struct Ull
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
}

#endif
