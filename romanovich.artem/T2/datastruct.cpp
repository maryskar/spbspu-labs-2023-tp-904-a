#include "datastruct.h"
#include <iostream>
using rDelimIO = romanovich::DelimiterIO;
using rDataStruct = romanovich::DataStruct;
std::istream &checkSentry(std::istream &in)
{
  std::istream::sentry sentry(in);
  return in;
}
std::istream &romanovich::operator>>(std::istream &in, romanovich::UnsignedLongLongIO &&dest)
{
  if (!checkSentry(in))
  {
    return in;
  }
  return in >> rDelimIO{'0'} >> dest.number;
}
std::istream &romanovich::operator>>(std::istream &in, romanovich::RationalNumberIO &&dest)
{
  if (!checkSentry(in))
  {
    return in;
  }
  return in >> rDelimIO{'('} >> rDelimIO{':'} >> rDelimIO{'N'}
            >> dest.ratNumber.first >> rDelimIO{':'} >> rDelimIO{'D'}
            >> dest.ratNumber.second >> rDelimIO{':'} >> rDelimIO{')'};
}
std::istream &romanovich::operator>>(std::istream &in, romanovich::StringIO &&dest)
{
  if (!checkSentry(in))
  {
    return in;
  }
  return std::getline(in >> rDelimIO{'"'}, dest.string, '"');
}
std::istream &romanovich::operator>>(std::istream &in, rDelimIO &&dest)
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
std::ostream &romanovich::operator<<(std::ostream &out, const rDataStruct &source)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  romanovich::iofmtguard fmtguard(out);
  out << "(:key1 0" << source.key1 << ":key2 (:N " << source.key2.first << ":D " << source.key2.second
      << ":):key3 \"" << source.key3 << "\":)\n";
  return out;
}
void fillData(rDataStruct &dataStruct, std::istream &in)
{
  const std::string list[3] = {"key1", "key2", "key3"};
  std::string key, value;
  in >> key;
  if (key == list[0])
  {
    in >> romanovich::UnsignedLongLongIO{dataStruct.key1} >> rDelimIO{':'};
  }
  if (key == list[1])
  {
    /* Я не понимаю, что не так :(
     *
     * in >> romanovich::RationalNumberIO{dataStruct.key2} >> rDelimIO{':'};
     *
     * Когда я использую вот код выше вместо того, что ниже, поля RationalNumberIO не заполняются
     * При выводе их значения равны 0
     */

    in >> rDelimIO{'('} >> rDelimIO{':'} >> rDelimIO{'N'}
       >> dataStruct.key2.first >> rDelimIO{':'} >> rDelimIO{'D'}
       >> dataStruct.key2.second >> rDelimIO{':'} >> rDelimIO{')'}
       >> rDelimIO{':'};
  }
  if (key == list[2])
  {
    in >> romanovich::StringIO{dataStruct.key3} >> rDelimIO{':'};
  }
}
std::istream &romanovich::operator>>(std::istream &in, rDataStruct &dest)
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
romanovich::iofmtguard::iofmtguard(std::basic_ios< char > &s):
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  fmt_(s.flags())
{
}
romanovich::iofmtguard::~iofmtguard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}
bool romanovich::Comparator::operator()(const rDataStruct &lhs, const rDataStruct &rhs) const
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
