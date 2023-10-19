#ifndef IOTYPES_HPP
#define IOTYPES_HPP

#include <iostream>

namespace gulkov
{
  struct DelimiterIO
  {
    char delimeter_;
  };

  struct UnsignedLongLongIO
  {
    unsigned long long& ullref_;
  };

  struct CharIO {
    char& charref_;
  };

  struct LabelIO {
    std::string label_;
  };

  struct StringIO
  {
    std::string& string_;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest);
  std::istream& operator>>(std::istream& in, CharIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif
