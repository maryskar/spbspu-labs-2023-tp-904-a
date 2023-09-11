#ifndef T3_NEW_IOSTRUCTS_H
#define T3_NEW_IOSTRUCTS_H

#include <iostream>

namespace nesterov
{
  struct DelimiterIO
  {
    char exp;
  };

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
}

#endif
