#include "comparator.h"
using CData = const timofeev::DataStruct &;
bool timofeev::Comparator::operator()(CData lhs, CData rhs) const
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
