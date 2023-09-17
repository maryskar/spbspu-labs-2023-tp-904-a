#include "DataStruct.h"
bool zhukova::Comparator::operator()(const zhukova::DataStruct & lhs, const zhukova::DataStruct & rhs) const
{
  if (std::abs(lhs.key1) != std::abs(rhs.key1))
  {
    return std::abs(lhs.key1) < std::abs(rhs.key1);
  }
  else if (lhs.key2 != rhs.key2)
  {
    return lhs.key2 < rhs.key2;
  }
  return lhs.key3.length() < rhs.key3.length();
}
