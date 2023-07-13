#ifndef IO_WORK_HPP
#define IO_WORK_HPP

#include <istream>
#include <string>
#include "data-struct.hpp"

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

  struct LabelIO
  {
    std::string exp;
  };

  struct ULL8
  {
    std::string exp;
  };

  struct ULL10
  {
    unsigned long long exp;
  };

  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char > & s);
    ~iofmtguard();
  private:
    std::basic_ios< char > & s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };

  std::istream & operator>>(std::istream & in, DelimiterIO && dest);
  std::istream & operator>>(std::istream & in, StringIO && dest);
  std::istream & operator>>(std::istream & in, LabelIO && dest);
  std::istream & operator>>(std::istream & in, ULL8 && dest);
  std::istream & operator>>(std::istream & in, ULL10 && dest);
  std::istream & operator>>(std::istream & in, DataStruct & dest);
  std::ostream & operator<<(std::ostream & out, const DataStruct & dest);
}

#endif
