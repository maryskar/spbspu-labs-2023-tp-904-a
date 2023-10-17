#include "basic_io.h"
#include <iostream>

namespace kumachev {
  std::istream &operator>>(std::istream &istream, CharIO &&character)
  {
    std::istream::sentry sentry(istream);

    if (!sentry) {
      return istream;
    }

    char c = '\0';
    istream >> c;

    if (c != character.value) {
      istream.setstate(std::ios::failbit);
    }

    return istream;
  }
}
