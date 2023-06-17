#ifndef _IOTYPES_H
#define _IOTYPES_H
#include <string>
namespace romanovich
{
  struct UnsignedLongLongIO
  {
    unsigned long long &number;
  };
  struct RationalNumberIO
  {
    std::pair< long long, unsigned long long > &ratNumber;
  };
  struct StringIO
  {
    std::string &string;
  };
  struct DelimiterIO
  {
    char symbol;
  };
  std::istream &operator>>(std::istream &in, UnsignedLongLongIO &&dest);
  std::istream &operator>>(std::istream &in, RationalNumberIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
}
#endif
