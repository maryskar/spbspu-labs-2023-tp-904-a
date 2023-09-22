#include "dataStruct.h"

bool samoilenko::compareData(const DataStruct& lhs, const DataStruct& rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }
  else if (lhs.key2 != rhs.key2)
  {
    return std::abs(lhs.key2) < std::abs(rhs.key2);
  }
  else
  {
    return lhs.key3.length() < rhs.key3.length();
  }
}

std::istream& samoilenko::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
}
