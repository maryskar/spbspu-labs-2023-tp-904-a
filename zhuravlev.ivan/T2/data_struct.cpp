#include <iomanip>
#include <vector>
#include <iterator>
#include "iofmtguard.hpp"
#include "IO.hpp"

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
      in >> sep{ '(' };
      in >> sep{ ':' } >> label{ "key1" } >> binll{ input.key1 };
      in >> sep{ ' ' };
      in >> sep{ ':' } >> label{ "key2" } >> hexll{ input.key2 };
      in >> sep{ ' ' };
      in >> sep{ ':' } >> label{ "key3" } >> str{ input.key3 };
      in >> sep{ ' ' };
      in >> sep{ ')' };
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }
}
