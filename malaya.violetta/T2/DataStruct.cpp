#include "DataStruct.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <IOStreamsGuard.hpp>
#include <IOStructs.hpp>
std::istream & malaya::operator>>(std::istream & in, DataStruct & dest)
{
  std::istream::sentry istreamChecker(in);
  if (!istreamChecker)
  {
    return in;
  }
  in >> DelimiterIO{'('};
  if (!in)
  {
    return in;
  }
  in >> DelimiterIO{':'};
  if (!in)
  {
    return in;
  }
  bool isKey1 = false;
  bool isKey2 = false;
  bool isKey3 = false;
  double key1 = 0;
  unsigned long long key2 = 0;
  std::string key3 = " ";
  for (size_t i = 0; i < 3; i++)
  {
    in >> LabelIO{"key"};
    size_t keyNumber = 0;
    in >> keyNumber;
    switch (keyNumber)
    {
      case 1:
        if (isKey1)
        {
          in.setstate(std::ios::failbit);
        }
        in >> DoubleIO{key1};
        isKey1 = true;
        break;
      case 2:
        if (isKey2)
        {
          in.setstate(std::ios::failbit);
        }
        in >> UnsignedLongLongIO{key2};
        isKey2 = true;
        break;
      case 3:
        if (isKey3)
        {
          in.setstate(std::ios::failbit);
        }
        in >> StringIO{key3};
        isKey3 = true;
        break;
      default:
        in.setstate(std::ios::failbit);
    }
    in >> DelimiterIO{':'};
  }
  if (!in)
  {
    return in;
  }
  in >> DelimiterIO{')'};
  if (!in)
  {
    return in;
  }
  else
  {
    DataStruct data{key1, key2, key3};
    dest = data;
  }
  return in;
}
bool malaya::DataComparator::operator()(const DataStruct & left, const DataStruct & right)
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
    return left.key3.length() <= right.key3.length();
  }
}
std::ostream & malaya::operator<<(std::ostream & out, const DataStruct & data)
{
  std::ostream::sentry ostreamChecker(out);
  if (!ostreamChecker)
  {
    return out;
  }
  IOStreamsGuard guard(out);
  out << "(" << ":key1 " << std::fixed << std::setprecision(1) << data.key1 << "d";
  out << ":key2 0" << std::oct << data.key2;
  out << ":key3 \"" << data.key3 << "\":)";
  return out;
}
