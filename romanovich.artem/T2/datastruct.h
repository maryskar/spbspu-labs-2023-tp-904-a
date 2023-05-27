#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <string>
namespace romanovich
{
  struct DataStruct
  {
    unsigned long long key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
  std::istream &operator>>(std::istream &in, DataStruct &dest);
  struct Comparator
  {
    bool operator()(const DataStruct &lhs, const DataStruct &rhs) const;
  };
}
#endif
