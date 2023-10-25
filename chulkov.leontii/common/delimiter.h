#ifndef DELIMITER_H
#define DELIMITER_H
#include <string>

namespace chulkov {
  struct DelimiterIO {
    char exp;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
}

#endif
