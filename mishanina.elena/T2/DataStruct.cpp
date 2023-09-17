#include "DataStruct.h"
#include <iomanip>
#include <iotypes.h>
std::istream &mishanina::operator>>(std::istream &in, DataStruct &data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct dataStruct = {0, 0};
  std::size_t number = 0;
  in >> DelimiterIO{'('} >> DelimiterIO{':'};
  for (size_t i = 0; i < 3; i++)
  {
    in >> LabelIO{"key"};
    in >> number;
    if (number == 1)
    {
      in >> LongLongIO{dataStruct.key1} >> DelimiterIO{':'};
    }
    else if (number == 2)
    {
      in >> UnsignedLongLongIO{dataStruct.key2} >> DelimiterIO{':'};
    }
    else if (number == 3)
    {
      in >> StringIO{dataStruct.key3} >> DelimiterIO{':'};
    }
    if (!in)
    {
      return in;
    }
  }
  in >> DelimiterIO{')'};
  if (in)
  {
    data = dataStruct;
  }
  return in;
}
std::ostream &mishanina::operator<<(std::ostream &out, const DataStruct &data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  long long llk = data.key1;
  unsigned long long ullk = data.key2;
  out << '(';
  out << LongLongIO{llk};
  out << UnsignedLongLongIO{ullk};
  out << ":key3 " << std::quoted(data.key3, '"');
  out << ":)";
  return out;
}
bool mishanina::Comparator::operator()(const DataStruct &left, const DataStruct &right)
{
  if (left.key1 != right.key1)
  {
    return left.key1 < right.key1;
  }
  else if (left.key2 != right.key2)
  {
    return left.key2 < right.key2;
  }
  else
  {
    return left.key3.length() < right.key3.length();
  }
}
