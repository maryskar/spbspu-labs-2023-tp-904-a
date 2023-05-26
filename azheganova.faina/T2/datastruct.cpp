#include "datastruct.h"
#include "iofmtguard.h"

std::istream & azheganova::operator>>(std::istream & in, DataStruct & dest)
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
    using dbl = DoubleIO;
    using ull = UnsignedLongLongIO;
    using str = StringIO;
    in >> sep{ '{' };
    in >> label{ "key1" } >> sep{ ':' } >> dbl{ input.key1 };
    in >> sep{ ',' };
    in >> label{ "key2" } >> sep{ ':' } >> ull{ input.key2 };
    in >> sep{ ',' };
    in >> label{ "key3" } >> sep{ ':' } >> str{ input.key3 };
    in >> sep{ '}' };
  }
  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream & azheganova::operator<<(std::ostream & out, const Data & src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "{ ";
  out << "\"key1\": " << std::fixed << std::setprecision(1) << src.key1 << "d, ";
  out << "\"key2\": " << std::hex << data.key2;
  out << "\"key3\": " << src.key3;
  out << " }";
  return out;
}
