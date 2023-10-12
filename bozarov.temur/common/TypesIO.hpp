#ifndef T2_TYPESIO_HPP
#define T2_TYPESIO_HPP
#include <complex>
#include <iostream>

namespace bozarov
{
  struct DelimiterIO
  {
    char exp;
  };
  struct PostfixIO
  {
    std::string exp;
  };
  struct UnsignedLongLongI
  {
    unsigned long long &ref;
  };
  struct UnsignedLongLongO
  {
    const unsigned long long &ref;
  };
  struct ComplexI
  {
    std::complex< double > &ref;
  };
  struct ComplexO
  {
    const std::complex< double > &ref;
  };
  struct StringIO
  {
    std::string &ref;
  };
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, PostfixIO &&dest);
  std::istream &operator>>(std::istream &in, UnsignedLongLongI &&dest);
  std::istream &operator>>(std::istream &in, ComplexI &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::ostream &operator<<(std::ostream &out, const UnsignedLongLongO &&dest);
  std::ostream &operator<<(std::ostream &out, const ComplexO &&dest);
}
#endif
