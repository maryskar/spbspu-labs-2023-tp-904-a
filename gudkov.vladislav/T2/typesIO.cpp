#include "typesIO.h"
#include "scopeGuard.h"

std::istream &gudkov::operator>>(std::istream &in, DelimiterExpIO &&dest)
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

std::istream &gudkov::operator>>(std::istream &in, SuffixExpIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  iofmtguard fmtguard(in);

  in.unsetf(std::ios_base::skipws);

  if (dest.exp.size() == 0)
  {
    return in;
  }

  char c = '0';

  in >> c;

  if (in)
  {
    const bool isLower = islower(c);

    if (tolower(c) != tolower(dest.exp[0]))
    {
      in.setstate(std::ios::failbit);
    }
    else
    {
      for (size_t i = 1; i < dest.exp.size(); ++i)
      {
        in >> c;
        if (!in)
        {
          break;
        }
        else
        {
          if (tolower(c) != tolower(dest.exp[i]) || isLower != static_cast< bool >(islower(c)))
          {
            in.setstate(std::ios::failbit);
            break;
          }
        }
      }
    }
  }
  return in;
}

std::istream &gudkov::operator>>(std::istream &in, LongLongIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref >> SuffixExpIO{ "ll" };
}

std::istream &gudkov::operator>>(std::istream &in, UnsignedLongLongIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref >> SuffixExpIO{ "ull" };
}

std::istream &gudkov::operator>>(std::istream &in, StringIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterExpIO{ '"' }, dest.ref, '"');
}

std::istream &gudkov::operator>>(std::istream &in, LabelIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref;
}
