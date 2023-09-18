#include "DataStruct.hpp"
#include <string>
#include <iostream>
#include "InpOutTypes.hpp"
#include "Iofmtguard.hpp"

std::istream& zasulsky::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  double key1 = 0.0;
  long long key2 = 0;
  std::string key3 = "";
  bool inKey1 = false;
  bool inKey2 = false;
  bool inKey3 = false;
  int number = 0;
  in >> DelimiterIO{ '(' };
  while (!(inKey1 && inKey2 && inKey3) && in.good())
  {
    in >> LabelIO{ ":key" } >> number;
    if (number == 1 && !inKey1)
    {
      in >> DoubleI{ key1 };
      inKey1 = true;
    }
    else if (number == 2 && !inKey2)
    {
      in >> LongLongIO{ key2 };
      inKey2 = true;
    }
    else if (number == 3 && !inKey3)
    {
      in >> StringIO{ key3 };
      inKey3 = true;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> LabelIO{ ":)" };
  if (in)
  {
    dest = DataStruct{ key1, key2, key3 };
  }
  return in;
}
std::ostream& zasulsky::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard guard(out);
  out << "(";
  out << ":key1" << " " << DoubleO{ data.key1 };
  out << ":key2" << " " << data.key2 << "ll";
  out << ":key3" << " " << '"' << data.key3 << '"';
  out << ":)";
  return out;
}
bool zasulsky::compare(zasulsky::DataStruct& lhs,zasulsky::DataStruct& rhs)
{
  if (rhs.key1 > lhs.key1)
  {
    return 1;
  }
  else if (lhs.key1 == rhs.key1)
  {
    if (lhs.key2 == rhs.key2)
    {
      return rhs.key3.length() > lhs.key3.length();
    }
    return rhs.key2 > lhs.key2;
  }
  else
  {
    return 0;
  }
}
