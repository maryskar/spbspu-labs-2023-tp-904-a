#include "TypesIO.hpp"

#include <iomanip>
#include <bitset>
#include <algorithm>

std::istream& ilyak::operator>>(std::istream& in, ilyak::DelimiterIO&& dest)
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

std::istream& ilyak::operator>>(std::istream& in, ilyak::LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string data = "";
  in >> data;
  in.putback(data.back());
  data.pop_back();
  if (in && (data != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& ilyak::operator>>(std::istream& in, ilyak::LiteralIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (dest.exp.find(c) == std::string::npos))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& ilyak::operator>>(std::istream& in, ilyak::ULongLongBinI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  in >> DelimiterIO{ '0' } >> LiteralIO{ "bB" };
  std::bitset< 64 > bits = 0;
  in >> bits;
  if (in.fail())
  {
    return in;
  }
  dest.ref = bits.to_ullong();

  return in;
}

std::ostream& ilyak::operator<<(std::ostream& out, ilyak::ULongLongBinO&& dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  std::bitset< 64 > bits(dest.val);
  std::string str = bits.to_string();
  str.erase(0, str.find_first_not_of('0'));

  return out << "0b" << str;
}

std::istream& ilyak::operator>>(std::istream& in, ilyak::CharIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> ilyak::DelimiterIO{ '\'' } >> dest.ref >> ilyak::DelimiterIO{ '\'' };

  return in;
}

std::istream& ilyak::operator>>(std::istream& in, ilyak::StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  return std::getline(in >> ilyak::DelimiterIO{ '"' }, dest.ref, '"');
}
