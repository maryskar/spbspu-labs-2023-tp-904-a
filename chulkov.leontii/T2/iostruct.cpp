#include "iostruct.h"
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
    in >> dest.ref;
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

  std::istream &operator>>(std::istream &in, LabelIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    std::string data = "";
    if ((in >> StringIO{ data }) && (data != dest.exp)) {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
  }
}
///dsda