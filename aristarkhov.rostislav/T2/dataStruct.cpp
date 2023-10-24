#include "dataStruct.h"
#include <iomanip>
#include <iostream>
#include <streamGuard.h>
#include <iostruct.h>

std::istream& aristarkhov::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{'('} >> DelimiterIO{':'};
  for (size_t i = 0; i < 3; i++)
  {
    size_t key = 0;
    in >> LabelIO{"key"} >> key;
    if (key == 1)
    {
      in >> CharIO{data.key1};
    }
    else if (key == 2)
    {
      in >> RationalNumberIO{data.key2};
    }
    else if (key == 3)
    {
      in >> StringIO{data.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> DelimiterIO{':'};
  }
  in >> DelimiterIO{')'};
  return in;
}

std::ostream& aristarkhov::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  StreamGuard streamGuard(out);
  out << "(:key1 \'" << data.key1 << '\'';
  out << ":key2 (:N " << data.key2.first << ":D " << data.key2.second;
  out << ":):key3 \"" << data.key3 << "\":)";
  return out;
}

bool aristarkhov::compare(const DataStruct& lhs, const DataStruct& rhs)
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
