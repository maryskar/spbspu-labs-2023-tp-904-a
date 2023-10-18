#include "dataSrtuct.h"

namespace muhortov {
  bool comparator::operator()(const dataStruct &lhs, const dataStruct &rhs) const {
    if (std::abs(lhs.key1) != std::abs(rhs.key1)) {
      return std::abs(lhs.key1) < std::abs(rhs.key1);
    } else if (lhs.key2 != rhs.key2) {
      return lhs.key2 < rhs.key2;
    }
    return lhs.key3.length() < rhs.key3.length();
  }
}
