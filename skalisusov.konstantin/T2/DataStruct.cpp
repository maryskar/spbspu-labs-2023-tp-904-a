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
