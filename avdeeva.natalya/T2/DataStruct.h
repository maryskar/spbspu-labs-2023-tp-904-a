#ifndef SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
#define SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
#include <iostream>
#include <string>
namespace avdeeva
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
  };
  struct Comparator
  {
    bool operator()(const DataStruct & lhs, const DataStruct & rhs) const;
  };
}
#endif
