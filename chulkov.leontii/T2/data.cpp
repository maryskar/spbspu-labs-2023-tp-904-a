#include "data.h"
#include <iostream>
#include "iostruct.h"
#include "streamsguard.h"

namespace chulkov {
  std::string getUllBin(unsigned long long data)
  {
    unsigned long long var = data;
    if (var == 0) {
      return "0b0";
    }
    std::string res = "";
    while (var > 0) {
      res = std::to_string(var % 2) + res;
      var /= 2;
    }
    res = "0b0" + res;
    return res;
  }

  std::istream& operator>>(std::istream& in, Data& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    Data input;
    {
      using sep = DelimiterIO;
      using label = LabelIO;
      using chr = CharIO;
      using str = StringIO;
      in >> sep{'('};
      for (int i = 1; i <= 3; i++) {
        in >> label{":key"};
        size_t num = 0;
        in >> num;
        if (num == 1) {
          in >> UllIO{input.key1};
        } else if (num == 2) {
          in >> chr{input.key2};
        } else if (num == 3) {
          in >> str{input.key3};
        }
        if (!sentry) {
          return in;
        }
      }
      in >> sep{':'} >> sep{')'};
    }
    if (in) {
      dest = input;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Data& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry) {
      return out;
    }
    StreamGuard StreamGuard(out);
    std::string key1 = getUllBin(src.key1);
    out << "(:";
    out << "key1 " << key1 << ":";
    out << "key2"
        << " '" << src.key2 << "':";
    out << "key3 \"" << src.key3 << "\":)";
    return out;
  }

  bool Comparator::operator()(const Data& frst, const Data& sec)
  {
    if (frst.key1 == sec.key1) {
      if (frst.key2 == sec.key2) {
        return frst.key3.length() < sec.key3.length();
      }
      return frst.key2 < sec.key2;
    } else {
      return frst.key1 < sec.key1;
    }
  }
}
