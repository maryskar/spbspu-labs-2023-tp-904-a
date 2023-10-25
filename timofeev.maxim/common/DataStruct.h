#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <iostream>
#include <string>
#include <complex>
namespace timofeev
{
  using complex = std::complex< double >;
  struct DataStruct
  {
    double key1;
    complex key2;
    std::string key3;
  };
  struct DelimiterIO
  {
    char exp;
  };
  struct DoubleIO
  {
    double &ref;
  };
  struct ComplexIO
  {
    complex &cmp;
  };
  struct StringIO
  {
    std::string &ref;
  };
  struct LabelIO
  {
    std::string exp;
  };
  std::string getScientificDouble(double val);
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, DoubleIO &&dest);
  std::istream &operator>>(std::istream &in, ComplexIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
}
#endif
