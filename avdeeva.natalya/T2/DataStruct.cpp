#include "DataStruct.h"
bool avdeeva::Comparator::operator()(const DataStruct & lhs, const DataStruct & rhs) const
{
  if (lhs.key1 == rhs.key1)
  {
    if(lhs.key2 == rhs.key2)
    {
      return lhs.key3.size() < rhs.key3.size();
    }
    return lhs.key2 < rhs.key2;
  }
  return lhs.key1 < rhs.key1;
}
