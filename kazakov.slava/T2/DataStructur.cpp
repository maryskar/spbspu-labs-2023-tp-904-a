#include "DataStructur.h"

namespace kazakov
{
  std::ostream& operator<<(std::ostream& out, const DataStructur& p)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    out << "(" << ":" << "key1" << " " << p.key1 << "ll" << ":";
    out << "key2" << " " << "'" << p.key2 << "'" << ":";
    out << "key3" << " " << "\"" << p.key3 << "\"" << ":" << ")";
    return out;
  }
  std::istream& operator>>(std::istream& in, DataStructur& p)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    kazakov::DataStructur vrem;
    in >> ExpectedSymbol{ '(' } >> ExpectedSymbol{ ':' };
    std::string getin;
    for (size_t i = 0; i < 3; i++)
    {
      in >> getin;
      if (getin == "key1")
      {
        in >> vrem.key1;

      }
      if (getin == "key2")
      {
        in >> vrem.key2;
      }
      if (getin == "key3")
      {
        in >> vrem.key3;
      }

      in >> ExpectedSymbol{ ':' };
    }
    in >> ExpectedSymbol{ ')' };

    if (in)
    {
      p = vrem;
    }

    return in;
  }
  bool comparator(const DataStructur& p1, const DataStructur& p2)
  {
    if (p1.key1 == p2.key1 and p1.key2 == p2.key2)
    {
      return p1.key3 < p2.key3;
    }
    if (p1.key1 == p2.key1)
    {
      return p1.key2 < p2.key2;
    }
    return p1.key1 < p2.key1;
  }
}
