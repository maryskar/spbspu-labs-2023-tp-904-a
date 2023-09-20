#ifndef T3_IOSTRUCTURES_HPP
#define T3_IOSTRUCTURES_HPP
#include <string>
namespace litvin
{
  struct DelimiterIO
  {
    char exp;
  };
  struct DoubleIO
  {
    double & ref;
  };
  struct RationalIO
  {
    std::pair< long long, unsigned long long > & ref;
  };
  struct StringIO
  {
    std::string & ref;
  };
  struct LabelIO
  {
    std::string exp;
  };
  std::istream & operator>>(std::istream & in, DelimiterIO && dest);
  std::istream & operator>>(std::istream & in, DoubleIO && dest);
  std::istream & operator>>(std::istream & in, StringIO && dest);
  std::istream & operator>>(std::istream & in, LabelIO && dest);
  std::istream & operator>>(std::istream & in, RationalIO && dest);
}
#endif
