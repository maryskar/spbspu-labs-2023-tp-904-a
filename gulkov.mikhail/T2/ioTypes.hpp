#ifndef IOTYPES_HPP
#define IOTYPES_HPP

#include <iostream>

namespace gulkov
{
  struct DelimiterIO
  {
    char delimeter;
  };

  struct UnsignedLongLongIO
  {
    unsigned long long& ullref;
  };

  struct CharIO
  {
    char& charref;
  };

  struct LabelIO
  {
    std::string label;
  };

  struct StringIO
  {
    std::string& string;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest);
  std::istream& operator>>(std::istream& in, CharIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif
