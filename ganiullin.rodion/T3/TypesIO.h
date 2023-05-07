#ifndef TYPES_IO_H
#define TYPES_IO_H

#include <string>

namespace ganiullin {
  struct DelimiterIO {
    char exp;
  };
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
}
#endif