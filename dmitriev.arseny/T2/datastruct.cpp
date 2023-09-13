#include "datastruct.h"

bool dmitriev::compareDataStructures(const DataStruct& lhs, const DataStruct& rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }
  else if (lhs.key2 != rhs.key2)
  {
    return lhs.key2 < rhs.key2;
  }
  else
  {
    return lhs.key3.length() < rhs.key3.length();
  }
}

std::istream& dmitriev::operator>>(std::istream& inp, DataStruct& data)
{
  // TODO: вставьте здесь оператор return
}

std::ostream& dmitriev::operator<<(std::ostream& inp, const DataStruct& data)
{
  // TODO: вставьте здесь оператор return
}
