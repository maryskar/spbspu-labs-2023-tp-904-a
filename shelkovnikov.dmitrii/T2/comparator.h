#ifndef SPBSPU_LABS_2023_TP_904_A_COMPARATOR_H
#define SPBSPU_LABS_2023_TP_904_A_COMPARATOR_H
#include "data_struct.h"
namespace dimkashelk
{
  struct Comparator
  {
    bool operator()(const DataStruct &lhs, const DataStruct &rhs) const;
  };
}
#endif
