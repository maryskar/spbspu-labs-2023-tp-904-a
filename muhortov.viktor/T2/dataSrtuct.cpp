#include "dataSrtuct.h"
#include "io.h"

namespace muhortov {
  bool compare(const DataStruct &lhs, const DataStruct &rhs)
  {
    if (std::abs(lhs.key1) != std::abs(rhs.key1)) {
      return std::abs(lhs.key1) < std::abs(rhs.key1);
    } else if (lhs.key2 != rhs.key2) {
      return lhs.key2 < rhs.key2;
    }
    return lhs.key3.length() < rhs.key3.length();
  }

  std::istream &operator>>(std::istream &input, DataStruct &dest)
  {
    std::istream::sentry sentry(input);
    if (!sentry) {
      return input;
    }
    DataStruct in;
    using sep = delimiterIO;
    using comp = complexIO;
    using rat = rationalNumIO;
    using str = stringIO;
    input >> sep{'('};

    for (unsigned i = 0; i < 3; i++) {
      input >> labelIO{":key"};
      int num = 0;
      input >> num;
      if (input) {
        if (num == 1) {
          input >> comp{in.key1};
        } else if (num == 2) {
          input >> rat{in.key2};
        } else if (num == 3) {
          input >> str{in.key3};
        }
      }
    }

    input >> sep{':'};
    input >> sep{')'};

    if (input) {
      dest = in;
    }

    return input;
  }

  std::ostream &operator<<(std::ostream &output, const std::complex< double > &dest)
  {
    std::ostream::sentry sentry(output);
    if (!sentry) {
      return output;
    }
    output << "#c(" << dest.real() << ' ' << dest.imag() << ')';
    return output;
  }

  std::ostream &operator<<(std::ostream &output, const std::pair< long long, unsigned long long > &dest)
  {
    std::ostream::sentry sentry(output);
    if (!sentry) {
      return output;
    }
    output << "(:N " << dest.first << ":D " << dest.second << ":)";
    return output;
  }

  std::ostream &operator<<(std::ostream &output, const DataStruct &src)
  {
    std::ostream::sentry sentry(output);
    if (!sentry) {
      return output;
    }

    iofmtguard fmtguard(output);
    output << '(';
    output << ":key1 " << std::fixed << std::setprecision(1) << src.key1;
    output << ":key2 " << src.key2;
    output << ":key3 " << '\"' << src.key3 << '\"';
    output << ":)";
    return output;
  }
}
