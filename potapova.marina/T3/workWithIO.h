#ifndef WORKWITHIO
#define WORKWITHIO

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
}

#endif
