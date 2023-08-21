#include "data_struct.hpp"
#include <iomanip>
#include <vector>
#include <iterator>
#include "iofmtguard.hpp"
#include "IO.hpp"

using namespace zhuravlev;
bool compareData(const DataStruct& lhs, const DataStruct& rhs)
{
  return (lhs.key1 != rhs.key1) ? (lhs.key1 < rhs.key1): (lhs.key2 != rhs.key2) ? (lhs.key2 < rhs.key2): (lhs.key3.size() < rhs.key3.size());
}

std::istream& operator>>(std::istream& in, DataStruct& dest)
{
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
      using bin = BinIO;
      using hex = HexIO;
      using str = StringIO;
      in >> sep{ '(' };
      in >> label{ "key1" } >> sep{ ':' } >> BinIO{ input.key1 };
      in >> sep{ ',' };
      in >> label{ "key2" } >> sep{ ':' } >> HexIO{ input.key2 };
      in >> sep{ ',' };
      in >> label{ "key3" } >> sep{ ':' } >> StringIO{ input.key3 };
      in >> sep{ ')' };
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
  out << ":key1 0b" << src.key1;
  out << ":key2 0x" << std::hex << std::uppercase << src.key2;
  out << ":key3 \"" << src.key3;
  out << "\":)";
  return out;
}
