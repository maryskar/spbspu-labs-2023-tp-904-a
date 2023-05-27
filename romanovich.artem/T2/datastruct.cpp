#include <iostream>
#include <limits>
#include "iotypes.h"
#include "datastruct.h"
#include "iofmtguard.h"
namespace
{
  bool isSmaller(double a, double b, double epsilon)
  {
    double absA = std::abs(a);
    double absB = std::abs(b);
    double diff = std::abs(a - b);
    double minDouble = std::numeric_limits< double >::min();
    if (a < b)
    {
      return true;
    }
    if (a == 0 || b == 0 || diff < minDouble)
    {
      return diff < (epsilon * minDouble);
    }
    else
    {
      return diff / (absA + absB) < epsilon;
    }
  }
}
namespace romanovich
{
  std::ostream &operator<<(std::ostream &out, const DataStruct &source)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(:key1 0" << source.key1;
    out << ":key2 (:N " << source.key2.first << ":D " << source.key2.second;
    out << ":):key3 \"" << source.key3 << "\":)";
    return out;
  }
  void fillData(DataStruct &dataStruct, std::istream &in)
  {
    const std::string list[3] = {"key1", "key2", "key3"};
    std::string key, value;
    in >> key;
    if (key == list[0])
    {
      in >> UnsignedLongLongIO{dataStruct.key1} >> DelimiterIO{':'};
    }
    if (key == list[1])
    {
      in >> RationalNumberIO{dataStruct.key2} >> DelimiterIO{':'};
    }
    if (key == list[2])
    {
      in >> StringIO{dataStruct.key3} >> DelimiterIO{':'};
    }
  }
  std::istream &operator>>(std::istream &in, DataStruct &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct dataStruct;
    in >> DelimiterIO{'('} >> DelimiterIO{':'};
    for (size_t i = 0; i < 3; ++i)
    {
      fillData(dataStruct, in);
    }
    in >> DelimiterIO{')'};
    if (in)
    {
      dest = dataStruct;
    }
    return in;
  }
  bool Comparator::operator()(const DataStruct &lhs, const DataStruct &rhs) const
  {
    if (lhs.key1 != rhs.key1)
    {
      return lhs.key1 < rhs.key1;
    }
    else
    {
      double lhsDouble = lhs.key2.first / static_cast< double >(lhs.key2.second);
      double rhsDouble = rhs.key2.first / static_cast< double >(rhs.key2.second);
      if (lhsDouble != rhsDouble)
      {
        return isSmaller(lhsDouble, rhsDouble, 1e-6);
      }
      else
      {
        return lhs.key3.length() < rhs.key3.length();
      }
    }
  }
}
