#include "typesio.hpp"
#include <bitset>
#include <limits>
#include <iomanip>

std::istream &gulyaev::operator>>(std::istream &in, DelimiterIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  char delim = '0';
  in >> delim;
  if (in && (delim != dest.exp)) {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream &gulyaev::operator>>(std::istream &in, BinUnsignedLongLongI &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  in >> DelimiterIO{'0'} >> LiteralIO{"bB"};
  if (in) {
    std::string bin = "";
    std::getline(in, bin, ':');
    try {
      dest.ref = std::bitset< std::numeric_limits< unsigned long long >::digits >(bin).to_ullong();
    } catch (const std::invalid_argument &e) {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
std::istream &gulyaev::operator>>(std::istream &in, ComplexI &&dest)
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
std::istream &gulyaev::operator>>(std::istream &in, StringIO &&dest)
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
std::istream &gulyaev::operator>>(std::istream &in, LiteralIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  char literal = '0';
  in >> literal;
  if (in && (dest.exp.find(literal) == std::string::npos)) {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::ostream &gulyaev::operator<<(std::ostream &out, const BinUnsignedLongLongO &&dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  std::string bin = std::bitset< 64 >(dest.ref).to_string();
  bin.erase(0, bin.find('1'));
  out << "0b0" << bin;
  return out;
}
std::ostream &gulyaev::operator<<(std::ostream &out, const ComplexO &&dest)
{
  std::ostream::sentry sentry(out);
  if(!sentry) {
    return out;
  }
  out << std::fixed << std::setprecision(1);
  out << "#c(" << dest.ref.real() << " " << dest.ref.imag() << ")";
  return out;
}
