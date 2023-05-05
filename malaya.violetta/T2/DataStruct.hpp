#ifndef T2_DATASTRUCT_HPP
#define T2_DATASTRUCT_HPP
#include <string>
#include <iosfwd>
namespace malaya
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
  };
  std::istream & operator>>(std::istream & in, DataStruct & dest);
  std::ostream & operator<<(std::ostream & out, const DataStruct & data);
  struct DataComparator
  {
    bool operator()(const DataStruct & left, const DataStruct & right);
  };
}
#endif
