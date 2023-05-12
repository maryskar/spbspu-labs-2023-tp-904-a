#ifndef ROMANOVICH_ARTEM_DATASTRUCT_H
#define ROMANOVICH_ARTEM_DATASTRUCT_H
#include <string>
#include <utility>
#include <ios>
#include <iostream>
namespace romanovich
{
  struct DataStruct
  {
    unsigned long long key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };
  struct UnsignedLongLongIO
  {
    unsigned long long &number;
  };
  struct RationalNumberIO
  {
    std::pair< long long, unsigned long long > &ratNumber;
  };
  struct StringIO
  {
    std::string &string;
  };
  struct DelimiterIO
  {
    char symbol;
  };
  std::istream &operator>>(std::istream &in, UnsignedLongLongIO &&dest);
  std::istream &operator>>(std::istream &in, RationalNumberIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
  std::istream &operator>>(std::istream &in, DataStruct &dest);
  class iofmtguard
  {
  public:
    explicit iofmtguard(std::basic_ios< char > &s);
    ~iofmtguard();
  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
  struct Comparator
  {
    bool operator()(const DataStruct &lhs, const DataStruct &rhs) const;
  };
}
#endif
