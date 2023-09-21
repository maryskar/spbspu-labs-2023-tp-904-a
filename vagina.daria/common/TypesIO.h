#ifndef T2_TYPESIO_H
#define T2_TYPESIO_H
#include <iostream>
#include <string>

namespace vagina
{
  struct DoubleI
  {
    double &num;
  };
  struct DoubleO
  {
    const double num;
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
  struct LabelIO
  {
    std::string label;
  };
  std::istream& operator>>(std::istream &in, DoubleI &&dest);
  std::istream& operator>>(std::istream &in, BinUnsignedLongLongIO &&dest);
  std::istream& operator>>(std::istream &in, StringIO &&dest);
  std::istream& operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream& operator>>(std::istream &in, LiteralIO &&dest);
  std::istream& operator>>(std::istream &in, LabelIO &&dest);
  std::ostream& operator<<(std::ostream &out, const DoubleO &&dest);
}

#endif
