#include "iotypes.h"
namespace konchev
{
  std::istream &operator>>(std::istream &in, DelimiterIO &&data)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char s = '0';
    in >> s;
    if (in && (s != data.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::istream &operator>>(std::istream &in, LabelIO &&data)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    for (std::size_t i = 0; i < data.str.length(); i++)
    {
      in >> DelimiterIO{data.str[i]};
    }
    return in;
  }
  std::istream &operator>>(std::istream &in, LongLongIO &&data)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> std::dec >> data.ref >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
    return in;
  }
  std::istream &operator>>(std::istream &in, uLongLongIO &&data)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> std::hex >> data.ref;
    return in;
  }
  std::istream &operator>>(std::istream &in, StringIO &&data)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, data.ref,  '"' );
  }
}
