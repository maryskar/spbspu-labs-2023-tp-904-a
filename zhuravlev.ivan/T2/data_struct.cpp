#include "data_struct.hpp"
#include <iomanip>
#include <vector>
#include <iterator>
#include "iofmtguard.hpp"
#include "IO.hpp"


bool zhuravlev::compareData(const DataStruct& lhs, const DataStruct& rhs)
{
  return (lhs.key1 != rhs.key1) ? (lhs.key1 < rhs.key1): (lhs.key2 != rhs.key2) ? (lhs.key2 < rhs.key2): (lhs.key3.size() < rhs.key3.size());
}

std::istream& operator>>(std::istream& in, zhuravlev::DataStruct& dest);
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  {
    using sep = zhuravlev::DelimiterIO;
    using label = zhuravlev::LabelIO;
    using binll = zhuravlev::BinIO;
    using hexll = zhuravlev::HexIO;
    using str = zhuravlev::StringIO;
    in >> sep{ '(' } >> sep{ ':' };
    for (size_t i = 1; i <= 3; i++)
    {
      size_t num = 0;
      in >> label{ "key" } >> num;
      if (num == 1)
      {
        in >> dbl{ input.key1 } >> sep{ ':' };
      }
      else if (num == 2)
      {
        in >> ull{ input.key2 } >> sep{ ':' };
      }
      else if (num == 3)
      {
        in >> str{ input.key3 } >> sep{ ':' };
      }
      if (!sentry)
      {
        return in;
      }
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }
}

std::ostream& operator<<(std::ostream& out, const zhuravlev::DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(";
  out << ":key1 " << std::fixed << std::setprecision(1) << data.key1;
  out << ":key2 0x" << std::hex << std::uppercase << data.key2;
  out << ":key3 \"" << data.key3;
  out << "\":)";
  return out;
}

