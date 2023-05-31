#include "data_struct.h"

namespace kumachev {
  using cmp = DataStructComparator;

  static int compareRational(const rational &lhs, const rational &rhs)
  {
    auto lhsValue = static_cast< float >(lhs.first) / lhs.second;
    auto rhsValue = static_cast< float >(rhs.first) / rhs.second;
    auto diff = lhsValue - rhsValue;

    if (diff < 0) {
      return -1;
    } else if (diff > 0) {
      return 1;
    } else {
      return 0;
    }
  }

  bool cmp::operator()(const DataStruct &lhs, const DataStruct &rhs) const
  {
    if (lhs.key1 == rhs.key1) {
      if (compareRational(lhs.key2, rhs.key2) == 0) {
        return lhs.key3.size() <= rhs.key3.size();
      }

      return compareRational(lhs.key2, rhs.key2) < 0;
    }

    return lhs.key1 < rhs.key1;
  }
}
