#include "data_struct.h"
#include <iomanip>
#include <iofmtguard.h>
#include <TypesIO.h>
#include "get_abs_complex.h"

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
      double left = 0.0;
      double right = 0.0;
      left = getAbsComplex(lhs.key2);
      right = getAbsComplex(rhs.key2);
      return left < right;
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
      using cl = CmpLspI;
      using str = StringIO;
      in >> sep{ '(' } >> sep{ ':' };
      size_t num = 0;
      for (size_t i = 0; i < 3; i++)
      {
        ++num;
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
    CmpLspO key2{ src.key2 };
    out << "(:key1 '" << src.key1 << "'";
    out << ":key2 "  << key2;
    out << ":key3 " << std::quoted(src.key3, '"') << ":)";
    return out;
  }
}
