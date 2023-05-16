#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <istream>
#include <string>

namespace turkin
{
  struct DataStruct
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };

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

  struct ULL10
  {};

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
  std::istream & operator>>(std::istream & in, ULL10 && dest);
  std::istream & operator>>(std::istream & in, DataStruct & dest);
  std::ostream & operator<<(std::ostream & out, const DataStruct & dest);
}

#endif
