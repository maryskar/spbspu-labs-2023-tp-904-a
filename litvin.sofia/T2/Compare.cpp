#include "Compare.hpp"
bool litvin::Compare::operator()(const DataStruct & data1, const DataStruct & data2) const
{
  if (data1.key1 != data2.key1)
  {
    return data1.key1 < data2.key1;
  }
  else
  {
    if (data1.key2 != data2.key2)
    {
      return data1.key2 < data2.key2;
    }
    else
    {
      return data1.key3.length() <= data2.key3.length();
    }
  }
}
