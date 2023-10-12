#include "TypesIO.hpp"
#include "IOFmtGuard.hpp"
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
std::istream &bozarov::operator>>(std::istream &in, PostfixIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  iofmtguard fmtguard(in);
  in.unsetf(std::ios_base::skipws);
  if (dest.exp.size() == 0) {
    return in;
  }
  char c = '0';
  in >> c;
  if (in) {
    const bool isLower = islower(c);
    if (tolower(c) != tolower(dest.exp[0])) {
      in.setstate(std::ios::failbit);
    }
    else {
      for (size_t i = 1; i < dest.exp.size(); ++i) {
        in >> c;
        if (!in) {
          break;
        }
        else {
          if (tolower(c) != tolower(dest.exp[i]) || isLower != static_cast< bool >(islower(c))) {
            in.setstate(std::ios::failbit);
            break;
          }
        }
      }
    }
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
      in >> PostfixIO{"ull"};
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
    in >> DelimiterIO{')'};
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
