#include "iostruct.h"
#include <bitset>
#include <iostream>
#include <delimiter.h>

namespace chulkov {
  std::istream& operator>>(std::istream& in, UllIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    char pref = '0';
    in >> DelimiterIO{'0'} >> pref;
    if (pref != 'b' && pref != 'B') {
      in.setstate(std::ios::failbit);
      return in;
    }
    std::bitset< 64 > bits = 0;
    in >> bits;
    if (in.fail()) {
      return in;
    }
    dest.ref = bits.to_ullong();
    return in;
  }

  std::istream& operator>>(std::istream& in, CharIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    in >> DelimiterIO{'\''} >> dest.ref >> DelimiterIO{'\''};
    return in;
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    for (size_t i = 0; i < dest.exp.length(); i++) {
      in >> DelimiterIO{dest.exp[i]};
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
  }
}
