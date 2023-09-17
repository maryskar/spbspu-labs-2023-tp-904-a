#ifndef TYPES_IO_H
#define TYPES_IO_H

#include <string>

namespace ovsyannikov
{
  struct DelimiterIO
  {
    char exp;
  };

  struct StringIO
  {
    std::string& ref;
  };

  struct LabelIO
  {
    std::string exp;
  };

  struct ULongLongIO
  {
    unsigned long long& ref;
  };

  struct CharIO
  {
    char& ref;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, ULongLongIO&& dest);
  std::istream& operator>>(std::istream& in, CharIO&& dest);

}
#endif
