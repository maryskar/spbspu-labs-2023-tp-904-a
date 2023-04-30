#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iosfwd>
#include <limits>
#include <string>

namespace ganiullin {
  struct DataStruct {
    double key1;
    unsigned long long key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& src);

  struct Comparator {
    bool operator()(const DataStruct& lhs, const DataStruct rhs) const {
      if (lhs.key1 == rhs.key1) {
        if (lhs.key2 == rhs.key2) {
          return lhs.key3.length() < rhs.key3.length();
        }
        return lhs.key2 < rhs.key2;
      }
      return lhs.key1 < rhs.key1;
    }
  };
}  // namespace ganiullin
#endif
