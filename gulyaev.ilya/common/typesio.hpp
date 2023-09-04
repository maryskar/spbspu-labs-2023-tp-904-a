#ifndef T2_TYPESIO_HPP
#define T2_TYPESIO_HPP
#include <iostream>
#include <complex>

namespace gulyaev
{
  struct DelimiterIO
  {
    char exp;
  };
  struct BinUnsignedLongLongI
  {
    unsigned long long &ref;
  };
  struct BinUnsignedLongLongO
  {
    const unsigned long long ref;
  };
  struct ComplexI
  {
    std::complex< double > &ref;
  };
  struct ComplexO
  {
    const std::complex< double > ref;
  };
  struct StringIO
  {
    std::string &ref;
  };
  struct LiteralIO
  {
    std::string exp;
  };
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, BinUnsignedLongLongI &&dest);
  std::istream &operator>>(std::istream &in, ComplexI &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, LiteralIO &&dest);
  std::ostream &operator<<(std::ostream &out, const BinUnsignedLongLongO &&dest);
  std::ostream &operator<<(std::ostream &out, const ComplexO &&dest);
}
#endif
