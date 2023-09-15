#include "InpOutTypes.hpp"

std::istream& operator>>(std::istream& in, DelimiterIO&& ref)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (c != ref.exp && in)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const DelimiterIO& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  return out << data.exp;
}

std::istream& operator>>(std::istream& in, DblIO&& ref)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  double c = 0;
  in >> std::scientific >> c;
  ref.ref = c;
  return in;
}

std::istream& operator>>(std::istream& in, SllIO&& ref)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> ref.ref >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
  return in;
}

std::istream& operator>>(std::istream& in, StringIO&& ref)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  getline(in >> DelimiterIO{ '"' }, ref.ref, '"');
  return in;
}

std::istream& operator>>(std::istream& in, LabelIO&& ref)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (size_t i = 0; i < ref.exp.length(); i++)
  {
    in >> DelimiterIO{ ref.exp[i] };
  }
  return in;
}
