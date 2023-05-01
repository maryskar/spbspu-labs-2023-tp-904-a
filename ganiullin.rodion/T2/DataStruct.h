#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iosfwd>
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
    bool operator()(const DataStruct& lhs, const DataStruct rhs) const;
  };
}  // namespace ganiullin
#endif
