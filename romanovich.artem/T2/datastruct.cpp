#include "datastruct.h"
#include <iostream>
using romDelimIO = romanovich::DelimiterIO;
using romDataStruct = romanovich::DataStruct;
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
  return in >> romDelimIO{'0'} >> dest.number;
}
std::istream &romanovich::operator>>(std::istream &in, romanovich::RationalNumberIO &&dest)
{
  if (!checkSentry(in))
  {
    return in;
  }
  return in >> romDelimIO{'('} >> romDelimIO{':'} >> romDelimIO{'N'} >> dest.ratNumber.first
            >> romDelimIO{':'} >> romDelimIO{'D'} >> dest.ratNumber.second >> romDelimIO{':'}
            >> romDelimIO{')'};
}
std::istream &romanovich::operator>>(std::istream &in, romanovich::StringIO &&dest)
{
  if (!checkSentry(in))
  {
    return in;
  }
  return std::getline(in >> romDelimIO{'"'}, dest.string, '"');
}
std::istream &romanovich::operator>>(std::istream &in, romDelimIO &&dest)
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
std::ostream &romanovich::operator<<(std::ostream &out, const romDataStruct &source)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  romanovich::iofmtguard fmtguard(out);
  out << "(:key1 0" << source.key1 << ":key2 (:N " << source.key2.first << ":D " << source.key2.second << ":):key3 \""
      << source.key3 << "\":)\n";
  return out;
}
void fillData(romDataStruct &dataStruct, std::istream &in)
{
  const std::string list[3] = {"key1", "key2", "key3"};
  std::string key, value;
  in >> key;
  if (key == list[0])
  {
    in >> romanovich::UnsignedLongLongIO{dataStruct.key1} >> romDelimIO{':'};
  }
  if (key == list[1])
  {
    /* Я не понимаю, что не так :(
     *
     * in >> romanovich::RationalNumberIO{dataStruct.key2} >> romDelimIO{':'};
     *
     * Когда я использую вот код выше вместо того, что ниже, поля RationalNumberIO не заполняются
     * При выводе их значения равны 0
     */

    in >> romDelimIO{'('} >> romDelimIO{':'} >> romDelimIO{'N'} >> dataStruct.key2.first
       >> romDelimIO{':'} >> romDelimIO{'D'} >> dataStruct.key2.second >> romDelimIO{':'}
       >> romDelimIO{')'} >> romDelimIO{':'};
  }
  if (key == list[2])
  {
    in >> romanovich::StringIO{dataStruct.key3} >> romDelimIO{':'};
  }
}
std::istream &romanovich::operator>>(std::istream &in, romDataStruct &dest)
{
  if (!checkSentry(in))
  {
    return in;
  }
  romDataStruct dataStruct;
  in >> romDelimIO{'('} >> romDelimIO{':'};
  for (size_t i = 0; i < 3; ++i)
  {
    fillData(dataStruct, in);
  }
  in >> romDelimIO{')'};
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
bool romanovich::Comparator::operator()(const romanovich::DataStruct &lhs, const romanovich::DataStruct &rhs) const
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
