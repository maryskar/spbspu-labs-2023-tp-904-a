#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>

namespace dmitriev
{

  struct DataStruct
  {
    double key1;
    long long key2;

    std::string key3;
  };

  bool compareDataStructures(const DataStruct& lhs, const DataStruct& rhs);
  std::istream& operator>>(std::istream& inp, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);

}

#endif
