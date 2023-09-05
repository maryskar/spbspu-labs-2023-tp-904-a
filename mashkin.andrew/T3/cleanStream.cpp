#include <iostream>
#include <limits>
#include "cleanStream.h"

namespace mashkin
{
  constexpr auto maxSize = std::numeric_limits< std::streamsize >::max();
  void cleanStream(std::istream& inp)
  {
    inp.clear();
    inp.ignore(maxSize, '\n');
  }
}
