#include "data_struct.hpp"
#include <iomanip>
#include <vector>
#include <iterator>
#include "iofmtguard.hpp"
#include "IO_separators.hpp"
#include "IO_bin_hex_str.hpp"
#include "convert_to_bin.hpp"

namespace zhuravlev
{

  bool compareData(const DataStruct& lhs, const DataStruct& rhs)
  {
    if (lhs.key1 != rhs.key1)
    {
      return lhs.key1 < rhs.key1;
    }
    else if (lhs.key2 != rhs.key2)
    {
      return lhs.key2 < rhs.key2;
    }
    else
    {
      return lhs.key3.size() < rhs.key3.size();
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
      using sep = DelimiterIO;
      using label = LabelIO;
      using binll = BinIO;
      using hexll = HexIO;
      using str = StringIO;
      in >> sep{ '(' } >> sep{ ':' };
      for (size_t i = 1; i <= 3; i++)
      {
        size_t num = 0;
        in >> label{ "key" } >> num;
        if (num == 1)
        {
          in >> binll{ input.key1 } >> sep{ ':' };
        }
        else if (num == 2)
        {
          in >> hexll{ input.key2 } >> sep{ ':' };
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
    auto key1 = convertToBin(src.key1);
    iofmtguard fmtguard(out);
    out << "(";
    out << ":key1 " << key1;
    out << ":key2 0x" << std::hex << std::uppercase << src.key2;
    out << ":key3 \"" << src.key3;
    out << "\":)";
    return out;
  }
}
