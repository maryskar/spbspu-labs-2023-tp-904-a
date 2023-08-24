#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <iostream>
namespace fesenko
{
  struct DataStruct
  {
    double key1;
    char key2;
    std::string key3;
  };
  std::istream &operator>>(std::istream &in, DataStruct &value);
  std::ostream &operator<<(std::ostream &out, const DataStruct &value);
}
#endif
