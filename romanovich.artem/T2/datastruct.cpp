#include "datastruct.h"
#include <iostream>
#include "input.h"
/*romanovich::DataStruct::DataStruct(return_tuple tuple):
  key1(std::get< 0 >(tuple)),
  key2(std::get< 1 >(tuple)),
  key3(std::get< 2 >(tuple))
{
}*/
void romanovich::DataStruct::printDS() const
{
  std::cout << "(:key1 0" << key1
            << ":key2 (:N " << key2.first << ":D " << key2.second
            << ":):key3 " << key3 << ":)\n";
}
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
  return in >> dest.number >> romDelimIO{'u'} >> romDelimIO{'l'} >> romDelimIO{'l'};
}
std::istream &romanovich::operator>>(std::istream &in, romanovich::RationalNumberIO &&dest)
{
  if (!checkSentry(in))
  {
    return in;
  }
  return in >> romDelimIO{'('} >> romDelimIO{':'} >> romDelimIO{'N'}
            >> dest.ratNumber.first
            >> romDelimIO{':'} >> romDelimIO{'D'}
            >> dest.ratNumber.second
            >> romDelimIO{':'} >> romDelimIO{')'} >> romDelimIO{':'};
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
  if (in && (c != dest.char_))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::ostream &romanovich::operator<<(std::ostream &out, const romanovich::DataStruct &source)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  romanovich::iofmtguard fmtguard(out);
  /*out << "{ ";
  out << "\"key1\": " << std::fixed << std::setprecision(1) << source.key1 << "d, ";
  out << "\"key2\": " << source.key2;
  out << " }";*/
  out << "(:key1 0" << source.key1
      << ":key2 (:N " << source.key2.first << ":D " << source.key2.second
      << ":):key3 " << source.key3 << ":)\n";
  return out;
}
std::istream &romanovich::operator>>(std::istream &in, romanovich::DataStruct &dest)
{
  if (!checkSentry(in))
  {
    return in;
  }
  for (std::string line; std::getline(std::cin, line);)
  {
    safeReplace(line, ":D", ";D");
    safeReplace(line, ":)", ")");
    safeReplace(line, "(:", "(");
    line = tryRemoveBrackets(line);
    std::string keyNames[3] = {"key1", "key2", "key3"};
    try
    {
      return_tuple tuple = parseLine(line, ":", " ", keyNames);
      dest = romanovich::DataStruct{
        std::get< 0 >(tuple),
        std::get< 1 >(tuple),
        std::get< 2 >(tuple)
      };
    }
    catch (...)
    {
    }
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
