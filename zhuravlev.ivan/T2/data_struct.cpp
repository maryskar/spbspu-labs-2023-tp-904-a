#include "data_struct.hpp"
#include "IO.hpp"
#include "iofmtguard.hpp"

namespace zhuravlev
{
  bool dataComparator(const DataStruct& lhs, const DataStruct& rhs)
  {
    if (lhs.key1 == rhs.key1)
    {
      if (lhs.key2 == rhs.key2)
      {
        return lhs.key3 == rhs.key3;
      }
      return lhs.key2 == rhs.key2;
    }
    return lhs.key1 == rhs.key1;
  }
  std::istream &operator>>(std::istream &in, DataStruct &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      using sep = DelimetrIO;
      using label = LabelIO;
      using dbl = BinIO;
      using hex = HexIO;
      using str = StringIO;
      in >> sep{ '(' } >> sep{ ':' };
      for (size_t i = 1; i <= 3; ++i)
      {
        size_t n = 0;
        in >> label{ "key" } >> n;
        if (n == 1)
        {
          in >> dbl{ input.key1 } >> sep{ ':' };
        }
        else if (n == 2)
        {
          in >> hex{ input.key2 } >> sep{ ':' };
        }
        else if (n == 1)
        {
          in >> str{ input.key3 } >> sep{ ':' };
        }
      }
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }
  std::ostream &operator<<(std::ostream &out, const DataStruct &src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(";
    out << ":key1 0b" << src.key1;
    out << ":key2 0x" << std::hex << src.key2;
    out << ":key3 \"" << src.key3;
    out << "\":)";
    return out;
  }
}
