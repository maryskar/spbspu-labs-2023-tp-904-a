#include <iomanip>
#include "datastruct.h"
#include "IOFmtGuard.h"

std::istream &operator>>(std::istream &in, DataStruct &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  {
    using sep = DelimiterIO;
    using ull = BinUnsignedLongLongIO;
    using dbl = DoubleIO;
    using str = StringIO;
    std::string keyN = "";
    in >> sep{ '(' } >> sep { ':' };
    for (auto i = 1; i <= 3; i++)
    {
      in >> keyN;
      if (keyN == "key1")
      {
        in >> dbl{ input.key1 } >> sep { ':' };
      }
      else if (keyN == "key2")
      {
        in >> ull{ input.key2 } >> sep { ':' };
      }
      else if (keyN == "key3")
      {
        in >> str{ input.key3 } >> sep { ':' };
      }
      if (!sentry)
      {
        return in;
      }
    }
    if (input.key3 == "")
    {
      in.setstate(std::ios::failbit);
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }
}
std::ostream &operator<<(std::ostream &out, const DataStruct &src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(:";
  out << "key1 " << std::scientific << std::setprecision(2) << src.key1 << ":";
  out << "key2 " << "0b" << src.key2 << ":";
  out << "key3 " << std::quoted(src.key3);
  out << ":)";
  return out;
}
