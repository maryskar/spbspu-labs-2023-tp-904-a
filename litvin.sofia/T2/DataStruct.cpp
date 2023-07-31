#include "DataStruct.hpp"
#include <cmath>
#include <ScopeGuard.hpp>
#include <iostructures.hpp>
namespace litvin
{
  std::string convertToScientific(double num)
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
}
std::istream & litvin::operator>>(std::istream & in, DataStruct & dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  double key1 = 0.0;
  std::pair< long long, unsigned long long > key2{0, 0};
  std::string key3 = "";
  DataStruct input;
  bool hasKey1 = false;
  bool hasKey2 = false;
  bool hasKey3 = false;
  {
    using sep = DelimiterIO;
    using label = LabelIO;
    using dbl = DoubleIO;
    using rat = RationalIO;
    using str = StringIO;
    size_t num = 0;
    in >> sep{'('};
    for (size_t i = 0; i < 3; i++)
    {
      in >> sep{':'} >> label{"key"};
      in >> num;
      if (num == 1 && !hasKey1)
      {
        in >> dbl{key1};
        hasKey1 = true;
      }
      if (num == 2 && !hasKey2)
      {
        in >> rat{key2};
        hasKey2 = true;
      }
      if (num == 3 && !hasKey3)
      {
        in >> str{key3};
        hasKey3 = true;
      }
      if (!in)
      {
        return in;
      }
    }
    in >> sep{':'} >> sep{')'};
  }
  if (in && hasKey1 && hasKey2 && hasKey3)
  {
    dest.key1 = key1;
    dest.key2 = key2;
    dest.key3 = key3;
  }
  return in;
}
std::ostream & litvin::operator<<(std::ostream & out, const DataStruct & dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  ScopeGuard guard(out);
  out << "(";
  out << ":key1 ";
  out << convertToScientific(dest.key1);
  out << ':';
  out << "key2 ";
  out << "(:N " << dest.key2.first;
  out << ":D " << dest.key2.second << ":)";
  out << ":key3 " << '"' << dest.key3 << '"' << ":)";
  return out;
}
bool litvin::Compare::operator()(const DataStruct & data1, const DataStruct & data2) const
{
  if (data1.key1 != data2.key1)
  {
    return data1.key1 < data2.key1;
  }
  else
  {
    if (data1.key2 != data2.key2)
    {
      return data1.key2 < data2.key2;
    }
    else
    {
      return data1.key3.length() <= data2.key3.length();
    }
  }
}
