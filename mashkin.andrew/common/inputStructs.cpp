#include "inputStructs.h"
#include <bitset>
#include <iostream>

namespace mashkin
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
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

  std::istream& operator>>(std::istream& in, DoubleIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string dblStr;
    std::getline(in, dblStr, ':');
    if (dblStr.find("e") == std::string::npos)
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    dest.ref = stod(dblStr);
    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
    return in >> DelimiterIO{':'};
  }

  std::istream& operator>>(std::istream& in, UllIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string var;
    std::getline(in, var, ':');
    if (var.substr(0, 2) != "0b")
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    dest.ref = std::bitset< 64 >(var.substr(2)).to_ullong();
    return in;
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.exp;
  }
}
