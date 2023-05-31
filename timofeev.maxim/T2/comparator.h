#ifndef COMPARATOR_H
#define COMPARATOR_H
#include "DataStruct.h"
namespace timofeev
{
  struct Comparator
  {
    bool operator()(DataStruct lhs, DataStruct rhs) const;
  };
}
#endif
