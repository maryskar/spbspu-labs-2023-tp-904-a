#ifndef IOTYPES_H
#define IOTYPES_H
#include <string>
namespace fesenko
{
  struct DelimiterIO
  {
    char exp;
  };

  struct DoubleI
  {
    double &ref;
  };

  struct DoubleO
  {
    const double val;
  };

  struct CharIO
  {
    char &ref;
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
  std::istream &operator>>(std::istream &in, DoubleI &&dest);
  std::istream &operator>>(std::istream &in, CharIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
  std::ostream &operator<<(std::ostream &out, DoubleO &&dest);
}
#endif
