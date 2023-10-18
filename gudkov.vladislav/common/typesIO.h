#ifndef TYPES_IO_H
#define TYPES_IO_H

#include <string>

namespace gudkov
{
  struct DelimiterExpIO
  {
    char exp;
  };

  struct SuffixExpIO
  {
    std::string exp;
  };

  struct LongLongIO
  {
    long long &ref;
  };

  struct UnsignedLongLongIO
  {
    unsigned long long &ref;
  };

  struct StringIO
  {
    std::string &ref;
  };

  struct LabelIO
  {
    std::string &ref;
  };

  void clearStream(std::istream &in);

  std::istream &operator>>(std::istream &in, DelimiterExpIO &&dest);
  std::istream &operator>>(std::istream &in, SuffixExpIO &&dest);
  std::istream &operator>>(std::istream &in, LongLongIO &&dest);
  std::istream &operator>>(std::istream &in, UnsignedLongLongIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
}
#endif
