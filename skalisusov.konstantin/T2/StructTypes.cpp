#include "StructTypes.h"
#include <iomanip>

std::istream & skalisusov::operator>>(std::istream &in, LabelIO &&dest)
{
  std::istream::sentry CheckSentry(in);
  if(!CheckSentry)
  {
    return in;
  }
  std::string str;
  str = "";
  std::getline(in, str, 'y');
  str += 'y';
  if (in && (str != dest.label_))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream & skalisusov::operator>>(std::istream &in, DelimiterIO &&dest)
{
  std::istream::sentry CheckSentry(in);
  if (!CheckSentry)
  {
    return in;
  }
  char delim = '0';
  in >> delim;
  if (in && (delim != dest.exp_))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream & skalisusov::operator>>(std::istream &in, StringIO &&dest)
{
  std::istream::sentry CheckSentry(in);
  if(!CheckSentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{'"'},dest.str_,'"');
}
std::istream & skalisusov::operator>>(std::istream &in, DoubleLiteralFormatIO &&dest)
{
  std::istream::sentry CheckSentry(in);
  if (!CheckSentry)
  {
    return in;
  }
  return in >> dest.dublit_ >> DelimiterIO{ 'd' };
}
std::istream & skalisusov::operator>>(std::istream &in, DoubleSciencificFormatI &&dest)
{
  std::istream::sentry CheckSentry(in);
  if(!CheckSentry)
  {
    return in;
  }
  in >> std::scientific >> dest.dubscienI_;
  if(dest.dubscienI_ == 0)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::ostream & skalisusov::operator<<(std::ostream &out, const DoubleSciencificFormatO &&dest)
{
  std::ostream::sentry CheckSentry(out);
  if(!CheckSentry)
  {
    return out;
  }
  double number = dest.dubscienO_;
  int tenDegree = 0;
  while (number < 1 || number >= 10)
  {
    if (number <= 1)
    {
      number *= 10;
      tenDegree --;
    }
    else if (number >= 1)
    {
      number /= 10;
      tenDegree ++;
    }
  }
  return out << std::fixed << std::setprecision(1)  << number << (tenDegree > 0 ? "e+" : "e") << tenDegree;
}
