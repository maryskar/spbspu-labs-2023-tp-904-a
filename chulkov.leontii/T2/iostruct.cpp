#include "iostruct.h"

#include <bitset>
#include <iostream>

namespace chulkov {
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    char c = '0';
    if (!(in >> c) || (c != dest.exp)) {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, UllIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    std::string var;
    std::getline(in, var, ':');
    if (var.substr(0, 2) == "0b") {
      bool validFormat = true;
      for (char c : var.substr(2)) {
        if (c != '0' && c != '1') {
          validFormat = false;
          break;
        }
      }
      if (validFormat) {
        dest.ref = std::bitset< 64 >(var.substr(2)).to_ullong();
      } else {
        in.setstate(std::ios::failbit);
      }
    } else {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, CharIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    in >> dest.ref;
    return in;
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    for (size_t i = 0; i < dest.exp.length(); i++) {
      in >> DelimiterIO{dest.exp[i]};
    }
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
  }
}
