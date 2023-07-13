#include "data-struct.hpp"
#include <iomanip>
#include "iofmtguard.hpp"
#include "io-work.hpp"

bool turkin::Comparator::operator()(const turkin::DataStruct & lhs, const turkin::DataStruct & rhs) const
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

std::istream & turkin::operator>>(std::istream & in, DataStruct & dest)
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
    using ull10 = ULL10IO;
    using ull8 = ULL8IO;
    using str = StringIO;
    in >> sep{ '(' };
    for (unsigned int i = 0; i < 3; i++)
    {
      unsigned int id = 0;
      in >> label{ ":key" } >> id;
      if (id == 1)
      {
        in >> ull10{ input.key1 };
      }
      else if (id == 2)
      {
        in >> ull8{ input.key2 };
      }
      else if (id == 3)
      {
        in >> str{ input.key3 };
      }
    }
    in >> sep{ ':' };
  }
  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream & turkin::operator<<(std::ostream & out, const DataStruct & src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "{ ";
  out << "\"key1\": " << src.key1 << "ull, ";
  out << "\"key2\": " << src.key2 << "ull, ";
  out << "\"key3\": " << src.key3 << "str";
  out << " }";
  return out;
}
