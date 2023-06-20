#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "datastruct.h"

namespace tarasenko
{
  struct Comparator
  {
    bool operator()(const DataStruct& lhs, const DataStruct& rhs) const;
  };
}
#endif
