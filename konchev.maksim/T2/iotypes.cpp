#include "iotypes.h"
namespace konchev
{
  std::istream &operator>>(std::istream &in, delimiter &&data)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char s = '0';
    in >> s;
    if (in && s != data.exp)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::istream &operator>>(std::istream &in, label &&data)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    for (std::size_t i = 0; i < data.str.length(); i++)
    {
      in >> delimiter{data.str[i]};
    }
    return in;
  }
  std::istream &operator>>(std::istream &in, LongLong &&data)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> data.ref >> delimiter{'l'} >> delimiter{'l'};
    return in;
  }
  std::istream &operator>>(std::istream &in, uLongLong &&data)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> std::hex >> data.ref;
    return in;
  }
  std::istream &operator>>(std::istream &in, String &&data)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> delimiter{'"'}, data.ref, '"');
  }
}
