#ifndef TYPES_IO_H
#define TYPES_IO_H

#include <string>
#include "FormatGuard.h"

namespace ganiullin {
  struct DelimiterIO {
    char exp;
  };

  struct DoubleI {
    double& ref;
  };
  struct DoubleO {
    const double val;
  };

  struct StringIO {
    std::string& ref;
  };

  struct LabelIO {
    std::string exp;
  };

  struct ULongLongIO {
    unsigned long long& ref;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp)) {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, DoubleI&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    return in >> std::scientific >> dest.ref;
  }

  std::ostream& operator<<(std::ostream& out, const DoubleO&& dest) {  // FIXME
    std::ostream::sentry sentry(out);
    if (!sentry) {
      return out;
    }
    ganiullin::iofmtguard fmtguard(out);

    double value = dest.val;
    int exponent = 0;

    if (abs(value) < 1) {
      while (abs(value) * 10 < 10) {
        value *= 10;
        exponent--;
      }
    } else {
      while (abs(value) / 10 < 1) {
        value /= 10;
        exponent++;
      }
    }
    out << std::setprecision(1) << value << exponent;

    return out;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    std::string data = "";
    in >> data;
    in.putback(data.back());
    data.pop_back();
    if (in && (data != dest.exp)) {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, ULongLongIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    return in >> DelimiterIO{'0'} >> DelimiterIO{'x'} >> std::hex >> dest.ref;
  }
}  // namespace ganiullin
#endif
