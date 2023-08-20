#include "data_struct.h"
namespace dimkashelk
{
  bool Comparator::operator()(const DataStruct &lhs, const DataStruct &rhs) const
  {
    if (std::abs(lhs.key1) == std::abs(rhs.key1))
    {
      if (lhs.key2 == rhs.key2)
      {
        return lhs.key3.length() < rhs.key3.length();
      }
      return lhs.key2 < rhs.key2;
    }
    return std::abs(lhs.key1) < std::abs(rhs.key1);
  }
}
