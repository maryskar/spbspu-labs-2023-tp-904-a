#include "DataStruct.h"

std::istream &skalisusov::operator>>(std::istream &in, DoubleLiteralFormatIO &&dest)
{
  std::istream::sentry checkSentry(in);
  if(!checkSentry)
  {
    return in;
  }
  return in >> dest.real_ >> CoverIO{"Dd"};
}

std::istream &skalisusov::operator>>(std::istream &in, skalisusov::DelimiterIO &&dest)
{
  std::istream::sentry checkSentry(in);
  if(!checkSentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if(in && (c != dest.exp_))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
