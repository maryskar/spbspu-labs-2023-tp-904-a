#include "iotypes.h"
#include <iomanip>

std::istream &fesenko::operator>>(std::istream &in, DelimiterIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp)) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &fesenko::operator>>(std::istream &in, DoubleIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return in >> std::scientific >> dest.ref;
}

std::istream &fesenko::operator>>(std::istream &in, CharIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  char c = '\'';
  return in >> DelimiterIO{ c } >> dest.ref >> DelimiterIO{ c };
}

std::istream &fesenko::operator>>(std::istream &in, StringIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  char c ='\"';
  return std::getline(in >> DelimiterIO{ c }, dest.ref, c);
}

std::istream &fesenko::operator>>(std::istream &in, LabelIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  std::string data = "";
  if ((in >> StringIO{ data }) && (data != dest.exp)) {
    in.setstate(std::ios::failbit);
  }
  return in;
}
