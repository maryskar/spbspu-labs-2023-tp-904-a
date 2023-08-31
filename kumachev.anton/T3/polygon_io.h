#ifndef T3_POLYGON_IO_H
#define T3_POLYGON_IO_H

#include <iosfwd>
#include "polygon.h"

namespace kumachev {
  struct CharIO {
    char value;
  };

  std::istream &operator>>(std::istream &istream, CharIO &&character);
  std::istream &operator>>(std::istream &istream, Point &point);
  std::istream &operator>>(std::istream &istream, Polygon &polygon);
}

#endif
