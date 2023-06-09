#include "Structures.hpp"
#include "ScopeGuard.hpp"
#include <iomanip>
#include <cmath>
namespace litvin
{
  std::basic_string< char > convertToScientific(double num)
  {
    int pow = 0;
    if (std::abs(num) >= 10)
    {
      while (std::abs(num) >= 10)
      {
        num /= 10;
        ++pow;
      }
    }
    else if (std::abs(num) < 1 && num != 0)
    {
      while (std::abs(num) < 1)
      {
        num *= 10;
        --pow;
      }
    }
    num *= 10;
    int temp = std::round(num);
    std::string res = std::to_string(temp);
    res.insert(1ull, 1ull, '.');
    res += 'e';
    if (pow >= 0)
    {
      res += '+';
    }
    res += std::to_string(pow);
    return res;
  }
  std::istream & operator>>(std::istream & in, DelimiterIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::istream & operator>>(std::istream & in, DoubleIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    using sep = DelimiterIO;
    ScopeGuard guard(in);
    int integer = 0;
    size_t fractional = 0;
    int power = 0;
    double mantissa = 0.0;
    in >> integer >> sep{'.'} >> fractional >> sep{'e'} >> power;
    mantissa = integer + static_cast< double >(fractional) / 10;
    dest.ref = mantissa * std::pow(10, power);
    return in;
  }
  std::istream & operator>>(std::istream & in, StringIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
  }
  std::istream & operator>>(std::istream & in, LabelIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = " ";
    ScopeGuard guard(in);
    if ((in >> std::setw(3) >> data) && (data != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::istream & operator>>(std::istream & in, RationalIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    {
      using sep = DelimiterIO;
      in >> sep{'('} >> sep{':'} >> sep{'N'};
      in >> dest.ref.first >> sep{':'} >> sep{'D'};
      in >> dest.ref.second >> sep{':'} >> sep{')'};
      return in;
    }
  }
}
