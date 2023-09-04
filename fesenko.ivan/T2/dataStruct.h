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
  bool compare(const DataStruct &first, const DataStruct &second);
  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &src);
}
#endif
