#ifndef COMPARATOR_H
#define COMPARATOR_H
#include "DataStruct.h"
namespace timofeev
{
  struct Comparator
  {
    bool operator()(const timofeev::DataStruct &lhs, const timofeev::DataStruct &rhs) const;
  };
}
#endif
