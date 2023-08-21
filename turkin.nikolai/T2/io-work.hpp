#ifndef IO_WORK_HPP
#define IO_WORK_HPP

#include <istream>
#include <string>

namespace turkin
{
  struct DelimiterIO
  {
    char exp;
  };

  struct StringIO
  {
    std::string & ref;
  };

  struct ULL8IO
  {
    unsigned long long & ref;
  };

  struct ULL10IO
  {
    unsigned long long & ref;
  };

  struct KeyIO
  {
    unsigned & ref;
  };

  std::istream & operator>>(std::istream & in, DelimiterIO && dest);
  std::istream & operator>>(std::istream & in, StringIO && dest);
  std::istream & operator>>(std::istream & in, ULL8IO && dest);
  std::istream & operator>>(std::istream & in, ULL10IO && dest);
  std::istream & operator>>(std::istream & in, KeyIO && dest);
}

#endif
