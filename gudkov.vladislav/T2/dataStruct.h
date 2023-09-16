#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>

namespace gudkov
{
  struct Data
  {
    long long key1;
    unsigned long long key2;
    std::string key3;
  };

  std::istream &operator>>(std::istream &in, Data &dest);
  std::ostream &operator<<(std::ostream &out, const Data &dest);
  bool isLess(const Data &lhs, const Data &rhs);
}
#endif
