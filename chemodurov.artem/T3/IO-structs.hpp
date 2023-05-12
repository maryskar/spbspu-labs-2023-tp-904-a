#ifndef T2_IO_STRUCTS_HPP
#define T2_IO_STRUCTS_HPP
#include <string>

namespace chemodurov
{
  struct DelimiterIO
  {
    char exp;
  };

  struct DoubleIO
  {
    double & ref;
  };

  struct LongLongIO
  {
    long long & ref;
  };

  struct StringIO
  {
    std::string & ref;
  };

  struct LabelIO
  {
    std::string & ref;
  };

  bool checkInSentry(std::istream & in);
  std::istream & operator>>(std::istream & in, DelimiterIO && dest);
  std::istream & operator>>(std::istream & in, DoubleIO && dest);
  std::istream & operator>>(std::istream & in, LongLongIO && dest);
  std::istream & operator>>(std::istream & in, StringIO && dest);
  std::istream & operator>>(std::istream & in, LabelIO && dest);
}

#endif
