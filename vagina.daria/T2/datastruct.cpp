#include "datastruct.h"
#include <iomanip>
#include <vector>
#include <iterator>
#include <IOFmtGuard.h>
#include <TypesIO.h>

std::istream& vagina::operator>>(std::istream &in, DataStruct &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  {
    using sep = DelimiterIO;
    using ull = BinUnsignedLongLongIO;
    using dbl = DoubleI;
    using str = StringIO;
    using label = LabelIO;
    in >> sep{ '(' } >> sep { ':' };
    for (std::size_t i = 1; i <= 3; i++)
    {
      std::size_t num = 0;
      in >> label{ "key" } >> num;
      if (num == 1)
      {
        in >> dbl{ input.key1 } >> sep { ':' };
      }
      else if (num == 2)
      {
        in >> ull{ input.key2 } >> sep { ':' };
      }
      else if (num == 3)
      {
        in >> str{ input.key3 } >> sep { ':' };
      }
      if (!sentry)
      {
        return in;
      }
    }
    if (input.key3 == "" || input.key1 == 0)
    {
      in.setstate(std::ios::failbit);
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }
}
std::ostream& vagina::operator<<(std::ostream &out, const DataStruct &src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(:";
  out << "key1 " << DoubleO{src.key1};
  out << ":key2 0b0";
  unsigned long long num = src.key2;
  std::vector < unsigned long long > vect;
  int i = 0;
  while (num)
  {
    vect.push_back(num % 2);
    num /= 2;
    i++;
  }
  std::copy(vect.rbegin(), vect.rend(), std::ostream_iterator< int >(out));
  out << ":key3 " << std::quoted(src.key3);
  out << ":)";
  return out;
}
bool vagina::comp(const DataStruct& lhs, const DataStruct& rhs)
{
  if (lhs.key1 == rhs.key1)
  {
    return (lhs.key2 == rhs.key2) ? lhs.key3.length() < rhs.key3.length() : lhs.key2 < rhs.key2;
  }
  return lhs.key1 < rhs.key1;
}
