#include "point.h"

namespace kryuchkova
{
  std::istream & operator>>( std::istream & in, Point & pos)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> "(" >> pos.x >> ";" >> pos.y >> ")";
    return in; 
  }
}