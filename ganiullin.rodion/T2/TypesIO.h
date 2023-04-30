#ifndef TYPES_IO_H
#define TYPES_IO_H

#include <iomanip>
#include <sstream>
#include <string>

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

std::ostream& operator<<(std::ostream& out, const DoubleO&& dest) {
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }

  std::ostringstream oss;
  oss << std::setprecision(1) << std::scientific << dest.val;
  std::string tmp = oss.str();
  size_t ePos = tmp.find("e");

  out << tmp.substr(0, ePos) + tmp.substr(ePos, 2);
  size_t i = ePos + 2;
  while (tmp[i] == '0' && tmp.size() > i + 1) {
    i++;
  }

  out << tmp.substr(i);
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

#endif
