#include "comparator.h"

bool tarasenko::Comparator::operator()(const DataStruct& lhs, const DataStruct& rhs) const
{
  if (lhs.key1 == rhs.key1)
  {
    if (lhs.key2 == rhs.key2)
    {
      return lhs.key3.length() < rhs.key3.length();
    }
    return lhs.key2 < rhs.key2;
  }
  return lhs.key1 < rhs.key1;
}
