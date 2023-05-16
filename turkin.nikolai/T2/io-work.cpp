#include "io-work.hpp"
#include <iomanip>

std::istream & operator>>(std::istream & in, turkin::DelimiterIO && dest)
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

std::istream & operator>>(std::istream & in, turkin::StringIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> turkin::DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream & operator>>(std::istream & in, turkin::LabelIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string data = "";
  if ((in >> turkin::StringIO{ data }) && (data != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & operator>>(std::istream & in, turkin::DataStruct & dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  turkin::DataStruct input;
  {
    using sep = turkin::DelimiterIO;
    using label = turkin::LabelIO;
    using ull10 = turkin::ULL10;
    using str = turkin::StringIO;
    in >> sep{ '{' };
    in >> label{ "key1" } >> sep{ ':' } >> ull10{ input.key1 };
    in >> sep{ ',' };
    in >> label{ "key2" } >> sep{ ':' } >> str{ input.key2 };
    in >> sep{ '}' };
  }
  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream & operator<<(std::ostream & out, const turkin::DataStruct & src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  turkin::iofmtguard fmtguard(out);
  out << "{ ";
  out << "\"key1\": " << std::fixed << std::setprecision(1) << src.key1 << "d, ";
  out << "\"key2\": " << src.key2;
  out << " }";
  return out;
}

turkin::iofmtguard::iofmtguard(std::basic_ios< char > & s) :
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  fmt_(s.flags())
{}

turkin::iofmtguard::~iofmtguard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}
