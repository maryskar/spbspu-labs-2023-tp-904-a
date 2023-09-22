#include "iotypes.h"

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

std::istream& samoilenko::operator>>(std::istream& in, Ull&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.n;
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
