#include "TypesIO.hpp"

#include <iomanip>
#include <bitset>
#include <algorithm>

std::istream& kabanov::operator>>(std::istream& in, kabanov::DelimiterIO&& dest)
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

std::istream& kabanov::operator>>(std::istream& in, kabanov::LabelIO&& dest)
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

std::istream& kabanov::operator>>(std::istream& in, kabanov::LiteralIO&& dest)
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

std::istream& kabanov::operator>>(std::istream& in, kabanov::ULongLongBinI&& dest)
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

std::ostream& kabanov::operator<<(std::ostream& out, kabanov::ULongLongBinO&& dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  std::bitset< 64 > bits(dest.val);
  std::string str = bits.to_string();
  str = '0' + str;
  size_t firstNonZero = str.find_first_not_of('0');
  if (firstNonZero == std::string::npos)
  {
    str = "0";
  }
  else
  {
    str.erase(0, str.find_first_not_of('0') - 1);
  }

  return out << "0b" << str;
}

std::istream& kabanov::operator>>(std::istream& in, kabanov::CharIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> kabanov::DelimiterIO{ '\'' } >> dest.ref >> kabanov::DelimiterIO{ '\'' };

  return in;
}

std::istream& kabanov::operator>>(std::istream& in, kabanov::StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  return std::getline(in >> kabanov::DelimiterIO{ '"' }, dest.ref, '"');
}
