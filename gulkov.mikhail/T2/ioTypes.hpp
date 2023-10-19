#ifndef IOTYPES_HPP
#define IOTYPES_HPP

#include <iostream>

namespace gulkov
{
  struct DelimiterIO
  {
    char exp;
  };

  struct UnsignedLongLongIO
  {
    unsigned long long& num;
  };

  struct CharIO {
    char& ref;
  };

  struct LabelIO {
    std::string exp;
  };

  struct StringIO
  {
    std::string& str;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest);
  std::istream& operator>>(std::istream& in, CharIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif
