#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <iostream>
#include <iomanip>

namespace mishanina
{
  struct DataStruct
  {
    DataStruct():
      key1(0),
      key2(0),
      key3("")
    {}
    long long key1;
    unsigned long long key2;
    std::string key3;
//    void output(std::ostream &out) const{
//      out << '(';
//      out << ":key1 " << key1;
//      out << ":key2 " << key2;
//      out << ":key3 " << std::quoted(key3, '"');
//      out << ":)";
//    }
  };
//  std::ostream &operator<<(std::ostream &out, const LongLongIO &dest);
//  std::ostream &operator<<(std::ostream &out, const UnsignedLongLongIO &dest);


//  std::ostream &operator<<(std::ostream &out,  const long long &dest)
//  {
//    out << dest << "ll";
//    return out;
//  }
//  std::ostream &operator<<(std::ostream &out, const unsigned long long &dest)
//  {
//    out << dest << "ull";
//    return out;
//  }
  std::istream &operator>>(std::istream &in, DataStruct &data);
  std::ostream &operator<<(std::ostream &out, const DataStruct &data);
  struct Comparator{
    bool operator()(const DataStruct &left, const DataStruct &right);
  };
}
#endif
