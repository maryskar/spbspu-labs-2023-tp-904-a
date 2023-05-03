#ifndef T2_SORT_H
#define T2_SORT_H

#include "data_struct.h"

namespace kumachev {
  int compareRational(const std::pair< long long, unsigned long long > &lhs,
      const std::pair< long long, unsigned long long > &rhs);

  bool compareData(const DataStruct &lhs, const DataStruct &rhs);
}

#endif //T2_SORT_H
