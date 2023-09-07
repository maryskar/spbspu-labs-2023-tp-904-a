#include "iotypes.h"
using namespace konchev;
std::ifstream &operator>>(std::ifstream &in, delimiter &&data)
{
  std::ifstream::sentry sentry(in);
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
std::ifstream &operator>>(std::ifstream &in, label &&data)
{
  std::ifstream::sentry sentry(in);
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
std::ifstream &operator>>(std::ifstream &in, LongLong &&data)
{
  std::ifstream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> data.ref >> delimiter{'l'} >> delimiter{'l'};
  return in;
}
std::ifstream &operator>>(std::ifstream &in, uLongLong &&data)
{
  std::ifstream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> std::hex >> data.ref;
  return in;
}
std::ifstream &operator>>(std::ifstream &in, String &&data)
{
  std::ifstream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> delimiter{'"'}, data.ref, '"');
}