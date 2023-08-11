#include "StructTypes.h"
#include <iomanip>

std::istream & skalisusov::operator>>(std::istream &in, LabelIO &&dest)
{
  std::istream::sentry CheckSentry(in);
  if(!CheckSentry)
  {
    return in;
  }
  std::string str = "";
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
  if(number < 1)
  {
    while(number < 1)
    {
      if(number >= 1)
      {
        break;
      }
      else
      {
        number *= 10;
        tenDegree --;
      }
    }
  }
  else
  {
    while(number >= 10)
    {
      number /=10;
      tenDegree ++;
    }
  }
  return out << std::fixed << std::setprecision(1)  << number << (tenDegree > 0 ? "e+" : "e") << tenDegree;
}
