#include <iomanip>
#include <vector>
#include <iterator>
#include "iofmtguard.hpp"
#include "IO.hpp"
#include "convert_to_bin.hpp"

namespace zhuravlev
{

  bool compareData(const DataStruct& lhs, const DataStruct& rhs)
  {
    return (lhs.key1 != rhs.key1) ? (lhs.key1 < rhs.key1): (lhs.key2 != rhs.key2) ? (lhs.key2 < rhs.key2): (lhs.key3.size() < rhs.key3.size());
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
      for (size_t i = 1; i <= 3; i++)
      {
        size_t num = 0;
        in >> label{ "key" } >> num;
        switch (num)
        {
          case '1':
            in >> binll{input.key1} >> sep{ ':' };
            break;
          case '2':
            in >> hexll{input.key2} >> sep{ ':' };
            break;
          case '3':
            in >> str{input.key3} >> sep{ ':' };
            break;  
          default:
            in.setstate(std::ios::failbit);
        }
      }
      if (in)
      {
        dest = input;
      }
      return in;
    }
  }
  std::ostream & operator<<(std::ostream& out, const DataStruct& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    auto key1 = convertToBin(src.key1);
    out << "(";
    out << ":key1 " << key1;
    out << ":key2 " << std::hex << std::uppercase << src.key2;
    out << ":key3 \"" << src.key3;
    out << "\":)";
    return out;
  }
}
