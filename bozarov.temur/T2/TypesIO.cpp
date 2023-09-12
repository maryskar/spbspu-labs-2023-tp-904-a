#include "TypesIO.hpp"
#include <iomanip>
#include <bitset>

std::istream &bozarov::operator>>(std::istream &in, DelimiterIO &&dest)
{
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
std::istream &bozarov::operator>>(std::istream &in, UnsignedLongLongI &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  if (in) {
    int num = 0;
    in >> num;
      if (in && num >= 0) {
      in >> LiteralIO{"ullULL"};
      dest.ref = num;
    }
  }
  return in;
}
std::istream &bozarov::operator>>(std::istream &in, ComplexI &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  in >> DelimiterIO{'#'} >> DelimiterIO{'c'} >> DelimiterIO{'('};
  if (in) {
    double num = 0;
    in >> num;
    std::complex< double > input;
    input.real(num);
    in >> num;
    input.imag(num);
    in >> DelimiterIO{')'} >> DelimiterIO{':'};
    if (in) {
      dest.ref = std::move(input);
    }
  }
  return in;
}
std::istream &bozarov::operator>>(std::istream &in, StringIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  in >> DelimiterIO{'"'},
  std::getline(in, dest.ref, '"');
  in >> DelimiterIO{':'};
  return in;
}
std::istream &bozarov::operator>>(std::istream &in, LiteralIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  std::string literal = "";
  std::getline(in, literal, ':');
  if (in && !(literal == dest.exp.substr(0, 3) || literal == dest.exp.substr(3, 3))) {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::ostream &bozarov::operator<<(std::ostream &out, const UnsignedLongLongO &&dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  out << dest.ref << "ull";
  return out;
}
std::ostream &bozarov::operator<<(std::ostream &out, const ComplexO &&dest)
{
  std::ostream::sentry sentry(out);
  if(!sentry) {
    return out;
  }
  out << std::fixed << std::setprecision(1);
  out << "#c(" << dest.ref.real() << " " << dest.ref.imag() << ")";
  return out;
}
