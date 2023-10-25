#include "io.h"

namespace muhortov {

  std::istream &operator>>(std::istream &input, delimiterIO &&dest)
  {
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

  std::istream &operator>>(std::istream &input, complexIO &&dest)
  {
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

  std::istream &operator>>(std::istream &input, stringIO &&dest)
  {
    std::istream::sentry sentry(input);
    if (!sentry) {
      return input;
    }
    return std::getline(input >> delimiterIO{'"'}, dest.str, '"');
  }

  std::istream &operator>>(std::istream &input, labelIO &&dest)
  {
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
}
