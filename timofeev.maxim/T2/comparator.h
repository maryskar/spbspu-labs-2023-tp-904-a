#ifndef COMPARATOR_H
#define COMPARATOR_H
#include "../common/DataStruct.h"
namespace timofeev
{
  struct Comparator
  {
    bool operator()(const DataStruct &lhs, const DataStruct &rhs);
  };
}
#endif
