#include "io.h"

namespace muhortov {

  std::istream &operator>>(std::istream &input, delimiterIO &&dest) {
    std::istream::sentry sentry(input);
    if (!sentry) {
      return input;
    }
    char chr = ' ';
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
    double first = 0.0;
    double second = 0.0;
    input >> labelIO{"#c("} >> first >> second >> delimiterIO{')'};
    dest.num = std::complex< double >(first, second);
    return input;
  }

  std::istream &operator>>(std::istream &input, rationalNumIO &&dest)
  {
    std::istream::sentry sentry(input);
    if (!sentry) {
      return input;
    }

    long long first = 0;
    unsigned long long second = 0;
    input >> labelIO{"(:N"} >> first >> labelIO{":D"} >> second >> labelIO{":)"};
    dest.num = std::pair< long long, unsigned long long >(first, second);
    return input;
  }

  std::istream &operator>>(std::istream &input, stringIO &&dest) {
    std::istream::sentry sentry(input);
    if (!sentry) {
      return input;
    }
    return std::getline(input >> delimiterIO{'"'}, dest.str, '"');
  }

  std::istream &operator>>(std::istream &input, labelIO &&dest) {
    std::istream::sentry sentry(input);
    if (!sentry) {
      return input;
    }
    char chr = ' ';
    for (size_t i = 0; i < dest.str.length(); i++) {
      input >> chr;
      if (input && (chr != dest.str[i])) {
        input.setstate(std::ios::failbit);
        break;
      }
    }
    return input;
  }

  std::istream &operator>>(std::istream &input, dataStruct &dest) {
    std::istream::sentry sentry(input);
    if (!sentry) {
      return input;
    }
    dataStruct in;
    using sep = delimiterIO;
    using comp = complexIO;
    using rat = rationalNumIO;
    using str = stringIO;
    input >> sep{'('};

    for (unsigned i = 0; i < 3; i++) {
      input >> labelIO{":key"};
      char num = ' ';
      input >> num;
      if (input) {
        if (num == '1') {
          input >> comp{in.key1};
        } else if (num == '2') {
          input >> rat{in.key2};
        } else if (num == '3') {
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

  std::ostream &operator<<(std::ostream &output, const std::complex< double > &dest) {
    std::ostream::sentry sentry(output);
    if (!sentry) {
      return output;
    }
    output << "#c(" << dest.real() << ' ' << dest.imag() << ')';
    return output;
  }

  std::ostream &operator<<(std::ostream &output, const std::pair< long long, unsigned long long > &dest) {
    std::ostream::sentry sentry(output);
    if (!sentry) {
      return output;
    }
    output << "(:N " << dest.first << ":D " << dest.second << ":)";
    return output;
  }

  std::ostream &operator<<(std::ostream &output, const dataStruct &src) {
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

  iofmtguard::iofmtguard(std::basic_ios< char > &s):
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {}

  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}
