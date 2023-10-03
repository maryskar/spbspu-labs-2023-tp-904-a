#include "OtherStructur.h"

namespace kazakov
{
  std::istream& operator>>(std::istream& in, ExpectedSymbol&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = 0;
    in >> c;
    if (in && (tolower(c) != tolower(dest.symbol)))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::istream& operator>>(std::istream& in, ExpectedString& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> ExpectedSymbol{ '\"' };
    if (in.fail())
    {
      return in;
    }
    std::getline(in, dest.string, '\"');
    return in;
  }
  std::istream& operator>>(std::istream& in, ExpectedLongLong& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> dest.ll;
    if (!in.fail())
    {
      in >> ExpectedSymbol{ 'l' } >> ExpectedSymbol{ 'l' };
      if (!in.fail())
      {
        return in;
      }
    }
    dest.ll = 0;
    return in;
  }
  std::istream& operator>>(std::istream& in, ExpectedChar& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> ExpectedSymbol{ '\'' };
    if (in.fail())
    {
      return in;
    }
    in >> dest.bukva >> ExpectedSymbol{ '\'' };
    return in;
  }
  std::ostream& operator<<(std::ostream& out, const ExpectedString& dest)
  {
    out << dest.string;
    return out;
  }
  std::ostream& operator<<(std::ostream& out, const ExpectedLongLong& dest)
  {
    out << dest.ll;
    return out;
  }
  std::ostream& operator<<(std::ostream& out, const ExpectedChar& dest)
  {
    out << dest.bukva;
    return out;
  }
  bool operator<(const ExpectedLongLong& dest, const ExpectedLongLong& otherdest)
  {
    return dest.ll < otherdest.ll;
  }
  bool operator<(const ExpectedLongLong& dest, long long chislo)
  {
    return dest.ll < chislo;
  }
  bool operator<(const ExpectedChar& dest, const ExpectedChar& otherdest)
  {
    return dest.bukva < otherdest.bukva;
  }
  bool operator<(const ExpectedString& dest, const ExpectedString& otherdest)
  {
    return dest.string.length() < otherdest.string.length();
  }
  bool operator==(const ExpectedChar& dest, const ExpectedChar& otherdest)
  {
    return dest.bukva == otherdest.bukva;
  }
  bool operator==(const ExpectedLongLong& dest, const ExpectedLongLong& otherdest)
  {
    return dest.ll == otherdest.ll;
  }
}
