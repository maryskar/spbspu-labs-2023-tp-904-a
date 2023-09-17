#include "data_struct.h"
#include <cmath>
#include <iostream>
#include <string>
#include <iomanip>
#include <iofmtguard.h>
#include <IOstructs.h>

namespace kryuchkova
{
  bool cmpData(const DataStruct & lhs, const DataStruct & rhs)
  {
    if (lhs.key1 != rhs.key1)
    {
      return lhs.key1 < rhs.key1;
    }
    else if (lhs.key2 != rhs.key2)
    {
      return lhs.key2 < rhs.key2;
    }
    else
    {
      return lhs.key3.size() < rhs.key3.size();
    }
  }

  std::string convertToSci(double data)
  {
    int n = 0;
    while (std::abs(data) >= 10)
    {
      data /= 10;
      ++n;
    }
    while (std::abs(data) < 1)
    {
      data *= 10;
      --n;
    }
    data *= 10;
    int val = std::round(data);
    std::string res = std::to_string(val);
    res.insert(1ull, 1ull, '.');
    res += 'e';
    if (n >= 0)
    {
      res += '+';
    }
    res += std::to_string(n);
    return res;
  }
  std::istream & operator>>(std::istream & in, DataStruct & dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      in >> Delimiter{ '(' } >> Delimiter{ ':' };
      for (size_t i = 1; i <= 3; i++)
      {
        size_t number = 0;
        in >> Label{ "key" } >> number;
        if (number == 1)
        {
          in >> DblSci{ input.key1 } >> Delimiter{ ':' };
        }
        else if (number == 2)
        {
          in >> UllOct{ input.key2 } >> Delimiter{ ':' };
        }
        else if (number == 3)
        {
          in >> String{ input.key3 } >> Delimiter{ ':' };
        }
      }
      if (in)
      {
        dest = input;
      }
      return in;
    }
  }

  std::ostream & operator<<(std::ostream & out, const DataStruct & source)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(";
    out << ":key1 " << convertToSci(source.key1);
    out << ":key2 0" << std::oct << source.key2;
    out << ":key3 \"" << source.key3;
    out << "\":)";
    return out;
  }

}
