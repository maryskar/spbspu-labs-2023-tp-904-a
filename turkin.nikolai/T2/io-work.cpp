#include "io-work.hpp"
#include <iomanip>
#include "iofmtguard.hpp"

std::istream & turkin::operator>>(std::istream & in, ULL10IO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref >> LabelIO{ "ULL" };
}

std::istream & turkin::operator>>(std::istream & in, ULL8IO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref >> LabelIO{ "ULL" };
}

std::istream & turkin::operator>>(std::istream & in, DelimiterIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & turkin::operator>>(std::istream & in, StringIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream & turkin::operator>>(std::istream & in, LabelIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string data = "";
  if ((in >> StringIO{ data }) && (data != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & turkin::operator>>(std::istream & in, DataStruct & dest)
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
    using ull10 = ULL10IO;
    using ull8 = ULL8IO;
    using str = StringIO;
    in >> sep{ '{' };
    in >> label{ "key1" } >> sep{ ':' } >> ull10{ input.key1 };
    in >> sep{ ',' };
    in >> label{ "key2" } >> sep{ ':' } >> ull8{ input.key2 };
    in >> sep{ '}' };
    in >> label{ "key3" } >> sep{ ':' } >> str{ input.key3 };
  }
  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream & turkin::operator<<(std::ostream & out, const DataStruct & src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "{ ";
  out << "\"key1\": " << std::fixed << std::setprecision(1) << src.key1 << "d, ";
  out << "\"key2\": " << src.key2;
  out << " }";
  return out;
}
