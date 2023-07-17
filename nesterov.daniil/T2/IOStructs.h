#ifndef T2_IOSTRUCTS_H
#define T2_IOSTRUCTS_H

#include <string>

namespace nesterov
{
  struct DelimiterIO
  {
    char exp;
  };

  struct StringIO
  {
    std::string &ref;
  };

  struct LabelIO
  {
    std::string &exp;
  };

  struct HexIO
  {
    unsigned long long &ref;
  };

  struct RationalIO
  {
    std::pair< long long, unsigned long long > &ref;
  };

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
  std::istream &operator>>(std::istream &in, HexIO &&dest);
  std::istream &operator>>(std::istream &in, RationalIO &&dest);
}

#endif
