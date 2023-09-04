#include "cleanSteam.h"
#include <limits>
#include <iostream>

namespace mashkin
{
  constexpr auto maxSize = std::numeric_limits< std::streamsize >::max();
  void cleanStream(std::istream& inp)
  {
    inp.clear();
    inp.ignore(maxSize, '\n');
  }
}
