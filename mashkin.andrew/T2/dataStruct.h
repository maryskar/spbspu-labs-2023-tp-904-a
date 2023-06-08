#ifndef T2_DATASTRUCT_H
#define T2_DATASTRUCT_H
#include <iostream>
#include <string>

namespace mashkin
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
  };

  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();

  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };

  struct Comparator
  {
    bool operator()(const DataStruct& first, const DataStruct& second);
  };

  std::istream& operator>>(std::istream& inp, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
}
#endif
