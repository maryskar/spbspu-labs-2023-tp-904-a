#include "dataStruct.h"
#include <bitset>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>

namespace mashkin
{
  std::string getDoubleString(double data)
  {
    std::string varString = std::to_string(data);
    size_t varPow = varString.find_first_not_of("0.");
    double dblWithMantissa = 0.0;
    std::string result;
    if (varPow > 1)
    {
      dblWithMantissa = data * std::pow(10, varPow - 1);
      result = std::to_string(dblWithMantissa) + "e-" + std::to_string(varPow - 1);
    }
    else
    {
      varPow = varString.find_first_of(".");
      dblWithMantissa = data / std::pow(10, (varPow - 1));
      result = std::to_string(dblWithMantissa) + "e+" + std::to_string(varPow - 1);
    }
    while (result.find_last_of('e') - 1 == result.find_last_of('0') &&
           result.find_last_of('0') != std::to_string(dblWithMantissa).find_last_not_of('0') + 1)
    {
      result.erase(std::begin(result) + result.find_last_of('0'));
    }
    {
      return result;
    }
  }

  std::string getUllBinStr(unsigned long long data)
  {
    unsigned long long varUll = data;
    std::string result = "";
    while (varUll)
    {
      result = std::to_string(varUll % 2) + result;
      varUll /= 2;
    }
    result = "0b0" + result;
    return result;
  }

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
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

  std::istream& operator>>(std::istream& in, DoubleIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
  }

  std::istream& operator>>(std::istream& in, UllIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string var;
    std::getline(in, var, ':');
    in.putback(':');
    if (var.substr(0, 2) != "0b")
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    dest.ref = std::bitset< 64 >(var.substr(2)).to_ullong();
    return in;
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    std::getline(in, data, 'y');
    data += 'y';
    if (data != dest.exp)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      using sep = DelimiterIO;
      using label = LabelIO;
      using dbl = DoubleIO;
      using str = StringIO;
      in >> sep{'('};
      for (size_t i = 0; i < 3; ++i)
      {
        size_t keyNum;
        in >> sep{':'} >> label{"key"} >> keyNum;
        if (keyNum == 1)
        {
          in >> dbl{input.key1};
        }
        else if (keyNum == 2)
        {
          in >> UllIO{input.key2};
        }
        else if (keyNum == 3)
        {
          in >> str{input.key3};
        }
        else
        {
          in.setstate(std::ios::failbit);
        }
      }
      in >> sep{':'} >> sep{')'};
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(:key1 " << getDoubleString(src.key1);
    out << ":key2 " << getUllBinStr(src.key2);
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
  }

  iofmtguard::iofmtguard(std::basic_ios< char >& s):
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {
  }

  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }

  bool Comparator::operator()(const DataStruct& first, const DataStruct& second)
  {
    if (first.key1 == second.key1)
    {
      if (first.key2 == second.key2)
      {
        return first.key3.length() < second.key3.length();
      }
      return first.key2 < second.key2;
    }
    else
    {
      return first.key1 < second.key1;
    }
  }
}
