#include "iostruct.h"
#include <iomanip>
#include <iostream>
#include "streamGuard.h"

std::istream& aristarkhov::operator>>(std::istream& in, DelimiterIO&& dest)
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

std::istream& aristarkhov::operator>>(std::istream& in, CharIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{'\''} >> dest.ref >> DelimiterIO{'\''};
  return in;
}

std::istream& aristarkhov::operator>>(std::istream& in, RationalNumberIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{'('} >> DelimiterIO{':'};
  in >> DelimiterIO{'N'} >> dest.ref.first;
  in >> DelimiterIO{':'};
  in >> DelimiterIO{'D'} >> dest.ref.second;
  return in >> DelimiterIO{':'} >> DelimiterIO{')'};
}

std::istream& aristarkhov::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
}

std::istream& aristarkhov::operator>>(std::istream& in, LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (size_t i = 0; i < dest.exp.length(); i++)
  {
    in >> DelimiterIO{dest.exp[i]};
  }
  return in;
}
