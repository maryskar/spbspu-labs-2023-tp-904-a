#ifndef SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
#define SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "iofmtguard.h"
#include "StructTypes.h"
#include <iostream>
namespace skalisusov
{
  struct DataStruct
  {
    double key1_;
    double key2_;
    std::string key3_;
  };
  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, DataStruct &src);
  bool comparate(DataStruct &firDs, DataStruct &secDs);
}
#endif //SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
