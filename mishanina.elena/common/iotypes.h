#ifndef IOTYPES_H
#define IOTYPES_H
#include <string>
namespace mishanina
{
  struct DelimiterIO
  {
    char exp;
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
    std::string exp;
  };
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, LongLongIO &&dest);
  std::istream &operator>>(std::istream &in, UnsignedLongLongIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);

  std::ostream &operator<<(std::ostream &out, const LongLongIO &dest);
  std::ostream &operator<<(std::ostream &out, const UnsignedLongLongIO &dest);

}
#endif
