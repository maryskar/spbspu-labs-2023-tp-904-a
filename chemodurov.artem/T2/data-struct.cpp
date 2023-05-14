#include "data-struct.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include "IO-structs.hpp"

namespace chemodurov
{
  std::string convertDoubleToSci(double a)
  {
    int pow = 0;
    if (std::abs(a) >= 10)
    {
      while (std::abs(a) >= 10)
      {
        a /= 10;
        ++pow;
      }
    }
    else if (std::abs(a) < 1)
    {
      while (std::abs(a) < 1)
      {
        a *= 10;
        --pow;
      }
    }
    a *= 10;
    int b = std::round(a);
    std::string res = std::to_string(b);
    res.insert(1ull, 1ull, '.');
    res += 'e';
    if (pow >= 0)
    {
      res += '+';
    }
    res += std::to_string(pow);
    return res;
  }

  std::istream & operator>>(std::istream & in, DataStrct & data)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStrct res;
    std::string temp;
    bool isKey1 = false;
    bool isKey2 = false;
    bool isKey3 = false;
    in >> DelimiterIO{'('};
    for (size_t i = 0; i < 3; ++i)
    {
      in >> LabelIO{temp};
      if (temp.substr(0, 3) == "key")
      {
        if (temp[3] == '1' && !isKey1)
        {
          in >> DoubleIO{res.key1};
          isKey1 = true;
        }
        else if (temp[3] == '2' && !isKey2)
        {
          in >> LongLongIO{res.key2};
          isKey2 = true;
        }
        else if (temp[3] == '3' && !isKey3)
        {
          in >> StringIO{res.key3};
          isKey3 = true;
        }
        else
        {
          in.setstate(std::ios::failbit);
        }
      }
    }
    in >> DelimiterIO{':'} >> DelimiterIO{')'};
    if (in)
    {
      data = res;
    }
    return in;
  }

  std::ostream & operator<<(std::ostream & out, const DataStrct & data)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    out << '(';
    out << ":key1 " << convertDoubleToSci(data.key1);
    out << ":key2 " << data.key2 << "ll";
    out << ":key3 \"" << data.key3;
    out << "\":)";
    return out;
  }

  bool isLess(const DataStrct & lhs, const DataStrct & rhs)
  {
    bool fst = lhs.key1 < rhs.key1;
    return fst || (lhs.key1 == rhs.key1 && lhs.key2 < rhs.key2) || (lhs.key2 == rhs.key2 && lhs.key3.size() < rhs.key3.size());
  }
}
