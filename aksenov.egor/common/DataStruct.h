#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <string>
#include <iostream>
#include <complex>
namespace aksenov
{
  struct DataStruct
  {
    unsigned long long key1;
    std::complex< double > key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char exp;
  };

  struct LabelIO
  {
    std::string exp;
  };

  struct UllIO
  {
    unsigned long long &ref;
  };

  struct StringIO
  {
    std::string &ref;
  };

  struct ComplexIO
  {
    std::complex< double > &complex;
  };

  struct HexFormat
  {
    const unsigned long long &hex;
  };
  std::ostream &operator<<(std::ostream &out, HexFormat &&hex);
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, UllIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, ComplexIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
}
#endif
