#include "data-struct.hpp"
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
    using ull10 = ULL10IO;
    using ull8 = ULL8IO;
    using str = StringIO;
    using key = KeyIO;
    in >> sep{ '(' };
    in >> sep{ ':' };
    for (unsigned i = 0; i < 3; i++)
    {
      unsigned k = 0;
      in >> key{ k };
      if (k == 1)
      {
        in >> ull10{ input.key1 };
      }
      if (k == 2)
      {
        in >> ull8{ input.key2 };
      }
      if (k == 3)
      {
        in >> str{ input.key3 };
      }
      in >> sep{ ':' };
    }
    in >> sep{ ')' };
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
  out << "(:";
  out << "key1 " << src.key1 << "ull:";
  out << "key2 0" << src.key2 << ":";
  out << "key3 " << "\"" << src.key3 << "\"";
  out << ":)";
  return out;
}
