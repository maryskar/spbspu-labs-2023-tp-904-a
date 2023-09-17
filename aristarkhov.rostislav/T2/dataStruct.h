#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>

namespace aristarkhov
{
  struct DataStruct
  {
    char key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
  bool compare(const DataStruct& first, const DataStruct& second);
}
#endif
