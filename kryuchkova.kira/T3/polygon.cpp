#include "polygon.h"
#include "../common/IOstructs.h"
#include <vector>

namespace kryuchkova
{
  std::istream & operator>>( std::istream & in, Polygon & polygon)
  {
    std::istream::sentry sentry(in);
    Point point;
    in >> point;
    polygon.points.push_back(point);
    while (in)
    {
      if (!sentry)
      {
        return in;
      }
      in >> Delimiter{' '} >> point;
      polygon.points.push_back(point);
    }
    return in;
  }
}
