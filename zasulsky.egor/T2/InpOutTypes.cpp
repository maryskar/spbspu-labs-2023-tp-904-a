#include "InpOutTypes.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include "Iofmtguard.hpp"

std::istream& zasulsky::operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char exp = '0';
  in >> exp;
  if (in && exp != dest.exp)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream& zasulsky::operator>>(std::istream& in, LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (size_t i = 0; i < dest.exp.length(); ++i)
  {
    in >> DelimiterIO{ dest.exp[i] };
  }
  return in;
}
std::istream& zasulsky::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.exp, '"');
}
std::istream& zasulsky::operator>>(std::istream& in, SllIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.num >> zasulsky::LabelIO{ "ll" };
}
std::istream& zasulsky::operator>>(std::istream& in, DblI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  int mantisa = 0;
  int number = 0;
  int power = 0;
  in >> mantisa >> DelimiterIO{ '.' } >> number >> DelimiterIO{ 'e' } >> power;
  dest.num = (mantisa * 1.0 + number * 0.01) * std::pow(10, power);
  return in;
}
std::ostream& zasulsky::operator<<(std::ostream& out, const DblO&& dest)
{
  std::ostream::sentry sentry(out);
  iofmtguard guard(out);
  if (!sentry)
  {
    return out;
  }
  double number = dest.num;
  int power = 0;
  while (std::abs(number) < 1)
  {
    number *= 10;
    power--;
  }
  while (std::abs(number) >= 10)
  {
    number /= 10;
    power++;
  }
  return out << std::fixed << std::setprecision(1) << number << 'e' << std::showpos << power;
}

