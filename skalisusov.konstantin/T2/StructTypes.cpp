#include "StructTypes.h"

namespace skalisusov
{
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
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
  std::istream &operator>>(std::istream &in, CoverIO &&dest)
  {
    std::istream::sentry CheckSentry(in);
    if(!CheckSentry)
    {
      return in;
    }
    std::string cover = "";
    if((in >> StringIO{cover}) && (cover != dest.cover_))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::istream &operator>>(std::istream &in, DoubleLiteralFormatIO &&dest)
  {
    std::istream::sentry CheckSentry(in);
    if (!CheckSentry)
    {
      return in;
    }
    return in >> dest.dublit_ >> DelimiterIO{ 'd' };
  }


}
