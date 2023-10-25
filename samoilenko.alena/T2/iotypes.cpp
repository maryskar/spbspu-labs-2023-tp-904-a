#include "iotypes.h"
#include <bitset>
#include <limits>

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
    try
    {
      dest.n = std::bitset< std::numeric_limits< unsigned long long >::digits >(binary).to_ullong();
    }
    catch(const std::invalid_argument& ex)
    {
      in.setstate(std::ios::failbit);
    }
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
