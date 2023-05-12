#include "datastruct.h"
#include <iostream>
namespace romanovich
{
  using rDelimIO = DelimiterIO;
  using rDataStruct = DataStruct;
  std::istream &checkSentry(std::istream &in)
  {
    std::istream::sentry sentry(in);
    return in;
  }
  std::istream &operator>>(std::istream &in, UnsignedLongLongIO &&dest)
  {
    if (!checkSentry(in))
    {
      return in;
    }
    return in >> rDelimIO{'0'} >> dest.number;
  }
  std::istream &operator>>(std::istream &in, RationalNumberIO &&dest)
  {
    if (!checkSentry(in))
    {
      return in;
    }
    std::pair< long long, unsigned long long > number;
    in >> rDelimIO{'('} >> rDelimIO{':'} >> rDelimIO{'N'}
       >> number.first >> rDelimIO{':'} >> rDelimIO{'D'}
       >> number.second >> rDelimIO{':'} >> rDelimIO{')'};
    if (in)
    {
      dest.ratNumber = number;
    }
    return in;
  }
  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    if (!checkSentry(in))
    {
      return in;
    }
    return std::getline(in >> rDelimIO{'"'}, dest.string, '"');
  }
  std::istream &operator>>(std::istream &in, rDelimIO &&dest)
  {
    if (!checkSentry(in))
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.symbol))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::ostream &operator<<(std::ostream &out, const rDataStruct &source)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(:key1 0" << source.key1 << ":key2 (:N " << source.key2.first << ":D "
        << source.key2.second << ":):key3 \"" << source.key3 << "\":)\n";
    return out;
  }
  void fillData(rDataStruct &dataStruct, std::istream &in)
  {
    const std::string list[3] = {"key1", "key2", "key3"};
    std::string key, value;
    in >> key;
    if (key == list[0])
    {
      in >> UnsignedLongLongIO{dataStruct.key1} >> rDelimIO{':'};
    }
    if (key == list[1])
    {
      in >> RationalNumberIO{dataStruct.key2} >> rDelimIO{':'};
    }
    if (key == list[2])
    {
      in >> StringIO{dataStruct.key3} >> rDelimIO{':'};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  std::istream &operator>>(std::istream &in, rDataStruct &dest)
  {
    if (!checkSentry(in))
    {
      return in;
    }
    rDataStruct dataStruct;
    in >> rDelimIO{'('} >> rDelimIO{':'};
    for (size_t i = 0; i < 3; ++i)
    {
      fillData(dataStruct, in);
    }
    in >> rDelimIO{')'};
    if (in)
    {
      dest = dataStruct;
    }
    return in;
  }
  iofmtguard::iofmtguard(std::basic_ios< char > &s):
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
  bool Comparator::operator()(const rDataStruct &lhs, const rDataStruct &rhs) const
  {
    if (lhs.key1 != rhs.key1)
    {
      return lhs.key1 < rhs.key1;
    }
    else if ((lhs.key2.first / lhs.key2.second) != (rhs.key2.first / rhs.key2.second))
    {
      return (lhs.key2.first / lhs.key2.second) < (rhs.key2.first / rhs.key2.second);
    }
    else
    {
      return lhs.key3.length() < rhs.key3.length();
    }
  }
}
