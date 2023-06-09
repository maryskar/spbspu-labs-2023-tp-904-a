#include "data_struct.hpp"

namespace zhuravlev
{
  bool dataComparator(const Data &lhs, const Data &rhs)
  {
    if (lhs.key1 == rhs.key1)
    {
      if (lhs.key2 == rhs.key2)
      {
        return lhs.key3 == rhs.key3;
      }
      return lhs.key2 == rhs.key2;
    }
    return lhs.key1 == rhs.key1;
  }
}
