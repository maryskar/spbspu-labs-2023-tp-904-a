#include "point.h"
#include <IOstructs.h>

namespace kryuchkova
{
  std::istream & operator>>( std::istream & in, Point & pos)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> Delimiter{'('} >> pos.x >> Delimiter{';'} >> pos.y >> Delimiter{')'};
    return in;
  }
}
