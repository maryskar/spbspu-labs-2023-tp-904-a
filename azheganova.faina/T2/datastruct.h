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
  std::istream & operator>>(std::istream & in, Data & dest);
  std::ostream & operator<<(std::ostream & out, const Data & dest);
}
#endif