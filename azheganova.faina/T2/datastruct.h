#ifndef DATASTRUCT_H
#define DATASTRUCH_H
#include <string>

namespace azheganova
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
  };
  bool comparator(const DataStruct & left, const DataStruct & right);
  std::istream & operator>>(std::istream & in, DataStruct & dest);
  std::ostream & operator<<(std::ostream & out, const DataStruct & dest);
}
#endif
