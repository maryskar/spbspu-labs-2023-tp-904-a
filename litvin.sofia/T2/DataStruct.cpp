#include "../DataStruct.hpp"
#include <iostream>
#include <iomanip>
namespace litvin
{
  std::istream & operator>>(std::istream & in, DataStruct & dest)
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
    {
      using sep = DelimiterIO;
      using label = LabelIO;
      using dbl = DoubleIO;
      using rat = RationalIO;
      using str = StringIO;
      size_t num = 0;
      bool hasKey1 = false;
      bool hasKey2 = false;
      bool hasKey3 = false;
      in >> sep{'('};
      for (int i = 0; i < 3; i++)
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
      }
      in >> sep{':'} >> sep{')'};
    }
    if (in)
    {
      dest.key1 = key1;
      dest.key2 = key2;
      dest.key3 = key3;
    }
    return in;
  }
  std::ostream & operator<<(std::ostream & out, const DataStruct & dest)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    ScopeGuard guard(out);
    out << "(";
    out << ":key1 ";
    sci(out, dest.key1);
    out << ':';
    out << "key2 ";
    out << "(:N " << dest.key2.first;
    out << ":D " << dest.key2.second << ":)";
    out << ":key3 " << '"' << dest.key3 << '"' << ":)";
    return out;
  }
}
