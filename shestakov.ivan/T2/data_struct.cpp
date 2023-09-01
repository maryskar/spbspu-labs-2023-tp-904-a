#include <iomanip>
#include <vector>
#include <iterator>
#include "TypesIO.h"
#include <cmath>

namespace shestakov
{

  bool compareValues(const DataStruct& lhs, const DataStruct& rhs)
  {
    if (lhs.key1 != rhs.key1)
    {
      return lhs.key1 < rhs.key1;
    }
    else if (lhs.key2 != rhs.key2)
    {
      return pow(pow(lhs.key2.real(), 2) + pow(lhs.key2.imag(), 2), 0.5) < pow(pow(rhs.key2.real(), 2) + pow(rhs.key2.imag(), 2), 0.5);
    }
    else
    {
      return lhs.key3.length() < rhs.key3.length();
    }
  }
  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      using sep = DelIO;
      using label = LabelIO;
      using chl = CharLitIO;
      using cl = CmpLspIO;
      using str = StringIO;
      in >> sep{ '(' } >> sep{ ':' };
      for (size_t i = 1; i <= 3; i++)
      {
        size_t num = 0;
        in >> label{ "key" } >> num;
        if (num == 1)
        {
          in >> chl{ input.key1 } >> sep{ ':' };
        }
        else if (num == 2)
        {
          in >> cl{ input.key2 } >> sep{ ':' };
        }
        else if (num == 3)
        {
          in >> str{ input.key3 } >> sep{ ':' };
        }
      }
      if (in)
      {
        dest = input;
      }
      return in;
    }

  }
  std::ostream& operator<<(std::ostream& out, const DataStruct& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(";
    out << ":key1 " << src.key1;
    out << ":key2 " << src.key2;
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
  }
}
