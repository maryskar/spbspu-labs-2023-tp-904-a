#ifndef T2_IOSTRUCTS_HPP
#define T2_IOSTRUCTS_HPP
#include <iosfwd>
#include <string>
namespace malaya
{
  struct DelimiterIO
  {
    char expression;
  };
  std::istream & operator>>(std::istream & in, DelimiterIO && dest);
  struct DoubleIO
  {
    double & reference;
  };
  std::istream & operator>>(std::istream & in, DoubleIO && dest);
  struct UnsignedLongLongIO
  {
    unsigned long long & reference;
  };
  std::istream & operator>>(std::istream & in, UnsignedLongLongIO && dest);
  struct StringIO
  {
    std::string & reference;
  };
  std::istream & operator>>(std::istream & in, StringIO && dest);
  struct LabelIO
  {
    std::string expression;
  };
  std::istream & operator>>(std::istream & in, LabelIO && dest);
}
#endif
