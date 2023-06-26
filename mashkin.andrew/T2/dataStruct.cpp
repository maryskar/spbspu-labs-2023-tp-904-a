#include "dataStruct.h"
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <inputStructs.h>
#include <outputStructs.h>

namespace mashkin
{
  std::string getDoubleString(double data)
  {
    std::string varString = std::to_string(data);
    size_t varPow = varString.find_first_not_of("0.");
    double mantissa = 0.0;
    std::string res;
    std::string eWithSign;
    if (varPow > 1)
    {
      mantissa = data * std::pow(10, varPow - 1);
      eWithSign = "e-" + std::to_string(varPow - 1);
    }
    else
    {
      varPow = varString.find_first_of(".");
      mantissa = data / std::pow(10, (varPow - 1));
      eWithSign = "e+" + std::to_string(varPow - 1);
    }
    res = std::to_string(mantissa);
    while (res.find_last_of('0') - 1 != res.find_last_not_of('0'))
    {
      res.erase(std::begin(res) + res.find_last_of('0'));
    }
    res += eWithSign;
    return res;
  }

  std::string getUllBinStr(unsigned long long data)
  {
    unsigned long long varUll = data;
    std::string res = "";
    while (varUll)
    {
      res = std::to_string(varUll % 2) + res;
      varUll /= 2;
    }
    res = "0b0" + res;
    return res;
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
      in >> sep{'('} >> sep{':'};
      for (size_t i = 0; i < 3; ++i)
      {
        std::string key;
        in >> label{key};
        if (key[3] == '1')
        {
          in >> dbl{input.key1};
        }
        else if (key[3] == '2')
        {
          in >> UllIO{input.key2};
        }
        else if (key[3] == '3')
        {
          in >> str{input.key3};
        }
        else
        {
          in.setstate(std::ios::failbit);
        }
      }
      in >> sep{')'};
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
