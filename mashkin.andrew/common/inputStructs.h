#ifndef MASHKIN_ANDREW_INPUTSTRUCTS_H
#define MASHKIN_ANDREW_INPUTSTRUCTS_H
#include <iostream>

namespace mashkin
{
  struct DelimiterIO
  {
    char exp;
  };

  struct DoubleIO
  {
    double& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  struct LabelIO
  {
    std::string& exp;
  };

  struct UllIO
  {
    unsigned long long& ref;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, DoubleIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, UllIO&& dest);
}
#endif
