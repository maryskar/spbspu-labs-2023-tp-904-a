#include "iotypes.h"
#include <bitset>
#include <limits>
#include <iomanip>

std::istream& samoilenko::operator>>(std::istream& in, Delimiter&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char a = '0';
  in >> a;
  if (in && (a != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& samoilenko::operator>>(std::istream& in, BinUll&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> Delimiter{'0'} >> Label{"b"};
  if (in)
  {
    std::string binary = "";
    std::getline(in, binary, ':');
    dest.n = std::bitset< std::numeric_limits< unsigned long long >::digits >(binary).to_ullong();
  }
  return in;
}

std::istream& samoilenko::operator>>(std::istream& in, ComplexNum&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  double realPart = 0.0;
  double imPart = 0.0;
  in >> Delimiter{'#'} >> Delimiter{'c'} >> Delimiter{'('};
  in >> realPart >> imPart >> Delimiter{')'};
  dest.cmpNum = std::complex< double >(realPart, imPart);
  return in;
}

std::istream& samoilenko::operator>>(std::istream& in, String&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> Delimiter{'"'}, dest.str, '"');
}

std::istream& samoilenko::operator>>(std::istream& in, Label&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (size_t k = 0; k < dest.exp.size(); k++)
  {
    in >> Delimiter{dest.exp[k]};
  }
  return in;
}

std::ostream& samoilenko::operator<<(std::ostream& out, BinUll&& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  std::string binary = std::bitset< 64 >(src.n).to_string();
  binary.erase(0, binary.find('1'));
  out << "0b" << binary;
  return out;
}

std::ostream& samoilenko::operator<<(std::ostream& out, ComplexNum&& src)
{
  std::ostream::sentry sentry(out);
  if(!sentry) {
    return out;
  }
  out << std::fixed << std::setprecision(1);
  out << "#c(" << src.cmpNum.real() << " " << src.cmpNum.imag() << ")";
  return out;

}
