#include "io.h"

namespace muhortov {
  std::istream &operator>>(std::istream &input, std::complex< double > &c) {
    std::istream::sentry sentry(input);
    if (!sentry) {
      return input;
    }
    double first = 0.0;
    double second = 0.0;

    input >> labelIO{"#c("} >> first >> second >> delimeterIO{')'};
    c = std::complex< double >(first, second);
    return input;
  }

  std::istream &operator>>(std::istream &input, std::pair< long long, unsigned long long > &c) {
    std::istream::sentry sentry(input);
    if (!sentry) {
      return input;
    }
    long long first = 0;
    unsigned long long second = 0;

    input >> labelIO{"(:N"} >> first >> labelIO{":D"} >> second >> labelIO{":)"};
    c = std::pair< long long, unsigned long long >(first, second);
    return input;
  }

  std::istream &operator>>(std::istream &input, delimeterIO &&dest) {
    std::istream::sentry sentry(input);
    if (!sentry) {
      return input;
    }
    char chr = '0';
    input >> chr;
    if (input && (chr != dest.chr)) {
      input.setstate(std::ios::failbit);
    }
    return input;
  }

  std::istream &operator>>(std::istream &input, complexIO &&dest) {
    std::istream::sentry sentry(input);
    if (!sentry) {
      return input;
    }
    return input >> dest.num;
  }

  std::istream &operator>>(std::istream &input, rationalNumIO &&dest)
  {
    std::istream::sentry sentry(input);
    if (!sentry) {
      return input;
    }
    return input >> dest.num;
  }

  std::istream &operator>>(std::istream &input, stringIO &&dest) {
    std::istream::sentry sentry(input);
    if (!sentry) {
      return input;
    }
    return input >> std::quoted(dest.str, '"');
  }

  std::istream &operator>>(std::istream &input, labelIO &&dest) {
    std::istream::sentry sentry(input);
    if (!sentry) {
      return input;
    }
    for (size_t i = 0; i < dest.str.length(); i++) {
      input >> delimeterIO{dest.str[i]};
    }
    return input;
  }

  std::istream &operator>>(std::istream &input, dataStruct &dest) {
    std::istream::sentry sentry(input);
    if (!sentry) {
      return input;
    }
    input >> delimeterIO{'('};
    std::complex< double > complexNum;
    std::pair< long long, unsigned long long > rationalNum;
    std::string str;

    for (unsigned i = 0; i < 3; i++) {
      size_t num = 0;
      input >> labelIO{":key"};
      input >> num;
      if (num == 1) {
        input >> complexIO{complexNum};
      } else if (num == 2) {
        input >> rationalNumIO{rationalNum};
      } else if (num == 3) {
        input >> stringIO{str};
      }
    }

    input >> labelIO{":)"};
    if (input) {
      dest = dataStruct{complexNum, rationalNum, str};
    }

    return input;
  }

  std::ostream &operator<<(std::ostream &output, const std::complex< double > &dest) {
    output << '(' << dest.real() << ' ' << dest.imag() << ')';
    return output;
  }

  std::ostream &operator<<(std::ostream &output, const std::pair< long long, unsigned long long > &dest) {
    output << "(:N " << dest.first << ":D " << dest.second << ":)";
    return output;
  }

  std::ostream &operator<<(std::ostream &output, const dataStruct &src) {
    std::ostream::sentry sentry(output);
    if (!sentry) {
      return output;
    }

    iofmtquard fmtquard(output);
    output << "(:key1 #c" << std::fixed << std::setprecision(1) << src.key1;
    output << ":key2 " << std::fixed << std::setprecision(1) << src.key2;
    output << ":key3 " << std::quoted(src.key3, '"') << ":)";
    return output;
  }

  muhortov::iofmtquard::iofmtquard(std::basic_ios< char > &s):
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {}

  muhortov::iofmtquard::~iofmtquard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }

}