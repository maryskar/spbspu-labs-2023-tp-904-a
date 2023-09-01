#ifndef SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
#define SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
#include <iostream>

namespace skalisusov
{
  struct DataStruct
  {
    double key1;
    double key2;
    std::string key3;
  };
  std::istream & operator>>(std::istream &in, DataStruct &dest);
  std::ostream & operator<<(std::ostream &out, const DataStruct &dest);
  bool comparator(const DataStruct &firDs, const DataStruct &secDs);
}
#endif
