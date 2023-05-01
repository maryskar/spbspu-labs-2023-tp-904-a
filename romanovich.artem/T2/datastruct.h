#ifndef ROMANOVICH_ARTEM_DATASTRUCT_H
#define ROMANOVICH_ARTEM_DATASTRUCT_H
#include <string>
#include <utility>
#include <ios>
#include <iostream>
#include "input.h"
namespace romanovich
{
  //using return_tuple = std::tuple< unsigned long long, std::pair< long long, unsigned long long >, std::string >;
  struct DataStruct
  {
    void printDS() const;
    static bool compareK1(const DataStruct &a, const DataStruct &b)
    {
      return a.key1 < b.key1;
    }
    static bool compareK2(const DataStruct &a, const DataStruct &b)
    {
      return (a.key2.first / a.key2.second) < (b.key2.first / b.key2.second);
    }
    static bool compareK3(const DataStruct &a, const DataStruct &b)
    {
      return a.key3.length() < b.key3.length();
    }
    static void print(const DataStruct &dataStruct)
    {
      dataStruct.printDS();
    }
    unsigned long long key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
    //explicit DataStruct(return_tuple tuple);
  };
  struct UnsignedLongLongIO
  {
    unsigned long long &number;
  };
  struct RationalNumberIO
  {
    std::pair< long long, unsigned long long > ratNumber;
  };
  struct StringIO
  {
    std::string &string;
  };
  struct DelimiterIO
  {
    char char_;
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
    std::basic_ios< char >::fmtflags fmt_{};
  };
}
using romDelimIO = romanovich::DelimiterIO;
using romDataStruct = romanovich::DataStruct;
void fillData(romDataStruct &dataStruct, std::istream &in);
#endif
