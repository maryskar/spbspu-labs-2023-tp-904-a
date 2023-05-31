#include "comparator.h"
using CData = const timofeev::DataStruct &;
bool timofeev::Comparator::operator()(CData lhs, CData rhs) const
{
  if (lhs.key1 == rhs.key1)
  {
    if (std::abs(lhs.key2) == std::abs(rhs.key2))
    {
      return lhs.key3.length() < rhs.key3.length();
    }
    return std::abs(lhs.key2) < std::abs(rhs.key2);
  }
  return lhs.key1 < rhs.key1;
}
