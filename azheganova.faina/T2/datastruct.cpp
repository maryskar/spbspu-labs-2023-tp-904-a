#include "datastruct.h"
#include <iomanip>
#include <vector>
#include <iterator>
#include "iofmtguard.h"
#include "iotypes.h"

bool azheganova::compareValues(const DataStruct & left, const DataStruct & right)
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

std::istream & azheganova::operator>>(std::istream & in, DataStruct & dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  {
    using sep = DelimiterIO;
    using label = LabelIO;
    using dbl = DoubleIO;
    using ull = UnsignedLongLongIO;
    using str = StringIO;
    in >> sep{ '(' } >> sep { ':' };
    for (size_t i = 1; i <= 3; i++)
    {
      size_t num = 0;
      in >> label{ "key" } >> num;
      if (num == 1)
      {
        in >> dbl{ input.key1 } >> sep{ ':' };
      }
      else if (num == 2)
      {
        in >> ull{ input.key2 } >> sep{ ':' };
      }
      else if (num == 3)
      {
        in >> str{ input.key3 } >> sep{ ':' };
      }
      if (!sentry)
      {
        return in;
      }
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }
}

std::ostream & azheganova::operator<<(std::ostream & out, const DataStruct & src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(";
  out << ":key1 " << std::fixed << std::setprecision(1) << src.key1 << "d";
  out << ":key2 0x" << std::hex << src.key2;
  out << ":key3 \"" << src.key3;
  out << "\":)";
  return out;
}
