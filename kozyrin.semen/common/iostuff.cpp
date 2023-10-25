#include "iostuff.h"

std::istream& kozyrin::operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  char c = '0';
  if (in >> c && c != dest.chr) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& kozyrin::operator>>(std::istream& in, LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  for (size_t i = 0; i < dest.str.length(); i++) {
    in >> DelimiterIO{dest.str[i]};
  }
  return in;
}

std::istream& kozyrin::operator>>(std::istream& in, DoubleIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  std::string str;
  std::getline(in, str, ':');
  if (str.find('e') != std::string::npos) {
    dest.val = std::stod(str);
  } else {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::istream& kozyrin::operator>>(std::istream& in, UllIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  in >> dest.val >> LabelIO{"ull"};
  return in;
}

std::istream& kozyrin::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return std::getline(in >> DelimiterIO{'"'}, dest.str, '"');
}
