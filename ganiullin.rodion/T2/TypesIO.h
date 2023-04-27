#ifndef TYPES_IO_H
#define TYPES_IO_H

#include <sstream>
#include <string>

struct DelimiterIO {
  char exp;
};

struct DoubleIO {
  double& ref;
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

std::istream& operator>>(std::istream& in, DoubleIO&& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return in >> std::scientific >> dest.ref;
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
#endif
