#ifndef WORKWITHIO_H
#define WORKWITHIO_H

#include "dataStructs.h"
#include <istream>
#include <ostream>

namespace potapova
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, Point& dest);
  std::ostream& operator<<(std::ostream& out, const Point& source);
  std::istream& operator>>(std::istream& in, Polygon& dest);
  std::ostream& operator<<(std::ostream& out, const Polygon& source);
  void handleInvalidCommand(std::istream& in, std::ostream& out);
}

#endif
