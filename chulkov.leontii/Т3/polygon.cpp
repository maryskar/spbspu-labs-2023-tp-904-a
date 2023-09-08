#include "polygon.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iostruct.h>

namespace chulkov {
  std::istream& operator>>(std::istream& in, Point& point)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    in >> DelimiterIO{'('} >> point.x >> DelimiterIO{';'} >> point.y >> DelimiterIO{')'};
    return in;
  }
}
