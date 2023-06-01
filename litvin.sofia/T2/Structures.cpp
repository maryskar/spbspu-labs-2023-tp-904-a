#include "structures.hpp"
#include "ScopeGuard.hpp"
#include <iomanip>
#include <cmath>
namespace litvin
{
  void sci(std::ostream & out, double num)
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
    else if (std::abs(num) < 1)
    {
      while (std::abs(num) < 1)
      {
        num *= 10;
        --pow;
      }
    }
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << num;
    std::string res = stream.str();
    res += 'e';
    if (pow >= 0)
    {
      res += '+';
    }
    res += std::to_string(pow);
    out << res;
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
    ScopeGuard guard(in);
    return in >> std::scientific >> dest.ref;
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
      using label = LabelIO;
      in >> sep{'('} >> sep{':'} >> sep{'N'};
      in >> dest.ref.first >> sep{':'} >> sep{'D'};
      in >> dest.ref.second >> sep{':'} >> sep{')'};
      return in;
    }
  }
}