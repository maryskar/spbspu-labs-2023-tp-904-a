#include "InpOutTypes.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include "Iofmtguard.hpp"

std::istream& zasulsky::operator>>(std::istream& in, DelimiterIO&& obj)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char exp = '0';
  in >> exp;
  if (in && exp != obj.exp)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream& zasulsky::operator>>(std::istream& in, LabelIO&& obj)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (size_t i = 0; i < obj.exp.length(); ++i)
  {
    in >> DelimiterIO{ obj.exp[i] };
  }
  return in;
}
std::istream& zasulsky::operator>>(std::istream& in, StringIO&& obj)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, obj.exp, '"');
}
std::istream& zasulsky::operator>>(std::istream& in, SllIO&& obj)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> obj.num >> zasulsky::LabelIO{ "ll" };
}
std::istream& zasulsky::operator>>(std::istream& in, DblI&& obj)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  int mantisa = 0;
  int num = 0;
  int pow = 0;
  in >> mantisa >> DelimiterIO{ '.' };
  in >> num >> DelimiterIO{ 'e' } >> pow;
  obj.num = (mantisa * 1.0 + num * 0.01) * std::pow(10, pow);
  return in;
}
std::ostream& zasulsky::operator<<(std::ostream& out, const DblO&& obj)
{
  std::ostream::sentry sentry(out);
  iofmtguard guard(out);
  if (!sentry)
  {
    return out;
  }
  double num = obj.num;
  int pow = 0;
  while (std::abs(num) < 1)
  {
    num *= 10;
    pow--;
  }
  while (std::abs(num) >= 10)
  {
    num /= 10;
    pow++;
  }
  out << std::fixed << std::setprecision(1);
  out << num << 'e' << std::showpos << pow;
  return out;
}
