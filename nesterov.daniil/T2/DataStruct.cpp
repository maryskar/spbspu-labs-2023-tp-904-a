#include "DataStruct.h"
#include <iostream>
#include <iomanip>
#include "IOStructs.h"
#include "IOFmtGuard.h"

namespace nesterov
{
  std::istream &operator>>(std::istream &in, DataStruct &dest)
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
      using str = StringIO;
      using hex = HexIO;
      using rat = RationalIO;

      std::string key;
      in >> sep{'('} >> sep{':'};

      for (size_t i = 0; i < 3; i++)
      {
        in >> label{key};
        if (key.size() < 4)
        {
          in.setstate(std::ios::failbit);
          return in;
        }
        if (key.substr(3) == "1")
        {
          in >> hex{input.key1};
        }
        else if (key.substr(3) == "2")
        {
          in >> rat{input.key2};
        }
        else if (key.substr(3) == "3")
        {
          in >> str{input.key3};
        }
        in >> sep{':'};
      }
      in >> sep{')'};
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::ostream &operator<<(std::ostream &out, const DataStruct &src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    IOFmtGuard fmtguard(out);
    out << "(:";
    {
      IOFmtGuard innerfmtguard(out);
      out << "key1 " << "0x" << std::hex << std::uppercase << src.key1 << ":";
    }
    out << "key2 " << "(:N " << src.key2.first << ":D " << src.key2.second << ":):";
    out << "key3 " << '"' << src.key3 << '"';
    out << ":)";
    return out;
  }

  bool DataStructComparator::operator()(const DataStruct &lhs, const DataStruct &rhs) const
  {
    if (lhs.key1 != rhs.key1)
    {
      return lhs.key1 < rhs.key1;
    }
    if (lhs.key2 != rhs.key2)
    {
      return lhs.key2.first / lhs.key2.second < rhs.key2.first / rhs.key2.second;
    }
    return lhs.key3 < rhs.key3;
  }
}
