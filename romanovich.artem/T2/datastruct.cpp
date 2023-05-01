#include <iostream>
#include "datastruct.h"
#include "input.h"
using romDelimIO = romanovich::DelimiterIO;
romanovich::DataStruct::DataStruct(return_tuple tuple):
  key1(std::get< 0 >(tuple)),
  key2(std::get< 1 >(tuple)),
  key3(std::get< 2 >(tuple))
{
}
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
std::istream &operator>>(std::istream &in, romanovich::UnsignedLongLongIO &&dest)
{
  if (!checkSentry(in))
  {
    return in;
  }
  return in >> dest.number >> romDelimIO{'u'} >> romDelimIO{'l'} >> romDelimIO{'l'};
}
std::istream &operator>>(std::istream &in, romanovich::RationalNumberIO &&dest)
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
  //return in >> dest.number >> romDelimIO{'u'} >> romDelimIO{'l'} >> romDelimIO{'l'};
}
std::istream &operator>>(std::istream &in, romanovich::StringIO &&dest)
{
  if (!checkSentry(in))
  {
    return in;
  }
  return std::getline(in >> romDelimIO{'"'}, dest.string, '"');
}
std::istream &operator>>(std::istream &in, romDelimIO &&dest)
{
  // все перегрузки операторов ввода/вывода должны начинаться с проверки экземпляра класса sentry
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