#include "delimiter.h"
#include <iostream>

namespace chulkov {
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    char c = '0';
    if (in >> c && (c != dest.exp)) {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}
