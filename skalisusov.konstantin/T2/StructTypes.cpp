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
  std::istream &operator>>(std::istream &in, DoubleSciencificFormatI &&dest)
  {
    std::istream::sentry CheckSentry(in);
    if(!CheckSentry)
    {
      return in;
    }
    return in >> std::scientific >> dest.dubscienI_;
  }
  std::ostream &operator<<(std::ostream &out, DoubleSciencificFormatO dest)
  {
    std::ostream::sentry CheckSentry(out);
    if(!CheckSentry)
    {
      return out;
    }
    double number = dest.dubscienO_;
    int tenDegree = 0;
    if(number < 1)
    {
      while(number < 10)
      {
        if(number > 1)
        {
          break;
        }
        else
        {
          number *= 10;
          tenDegree --;
        }
      }
    }
    else
    {
      while(number > 10)
      {
        number /=10;
        tenDegree ++;
      }
    }
    return out << std::fixed << std::setprecision(1)  << number << (tenDegree > 0 ? "e+" : "e") << tenDegree;
  }
  std::istream &operator>>(std::istream &in, skalisusov::StringIO &&dest)
  {
    std::istream::sentry CheckSentry(in);
    if(!CheckSentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'},dest.str_,'"');
  }
}
