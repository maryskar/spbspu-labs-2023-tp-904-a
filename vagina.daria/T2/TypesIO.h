#ifndef T2_TYPESIO_H
#define T2_TYPESIO_H
#include <iostream>
#include <string>

namespace vagina
{
  struct DoubleIO
  {
    double &num;
  };
  struct BinUnsignedLongLongIO
  {
    unsigned long long &num;
  };
  struct StringIO
  {
    std::string &string;
  };
  struct LiteralIO
  {
    std::string literal;
  };
  struct DelimiterIO
  {
    char symbol;
  };
  std::istream &operator>>(std::istream &in, DoubleIO &&dest);
  std::istream &operator>>(std::istream &in, BinUnsignedLongLongIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream& in, LiteralIO&& dest);
}

#endif
