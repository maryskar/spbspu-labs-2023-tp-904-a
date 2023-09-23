#ifndef COMMON_BASIC_IO_H
#define COMMON_BASIC_IO_H

#include <iosfwd>

namespace kumachev {
  struct CharIO {
    char value;
  };

  std::istream &operator>>(std::istream &istream, CharIO &&character);
}

#endif
