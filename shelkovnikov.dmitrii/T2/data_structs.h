#ifndef SPBSPU_LABS_2023_TP_904_A_DATA_STRUCTS_H
#define SPBSPU_LABS_2023_TP_904_A_DATA_STRUCTS_H
#include <complex>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
namespace dimkashelk
{
  using complex_type = std::complex< double >;
  using rational_number = std::pair< long long, unsigned long long >;
  struct DataStruct
  {
    complex_type key1;
    rational_number key2;
    std::string key3;
  };
  struct DelimiterIO
  {
    char exp;
  };
  struct ComplexIO
  {
    complex_type &ref;
  };
  struct RationalNumberIO
  {
    rational_number &ref;
  };
  struct StringIO
  {
    std::string &ref;
  };
  struct LabelIO
  {
    std::string exp;
  };
  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char > &s);
    ~iofmtguard();
  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
  std::istream &operator>>(std::istream &in, complex_type &&c);
  std::istream &operator>>(std::istream &in, rational_number &&c);
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, ComplexIO &&c);
  std::istream &operator>>(std::istream &in, RationalNumberIO &&c);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
}
#endif
