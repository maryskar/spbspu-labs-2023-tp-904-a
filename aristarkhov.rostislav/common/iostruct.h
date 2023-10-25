#ifndef IOSTRUCT_HPP
#define IOSTRUCT_HPP

#include <string>

namespace aristarkhov
{
  struct DelimiterIO
  {
    char exp;
  };

  struct RationalNumberIO
  {
    std::pair< long long, unsigned long long >& ref;
  };

  struct CharIO
  {
    char& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  struct LabelIO
  {
    std::string exp;
  };

  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, RationalNumberIO&& dest);
  std::istream& operator>>(std::istream& in, CharIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}
#endif
