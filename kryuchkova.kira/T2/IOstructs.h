#ifndef IOSTRUCTS_H
#define IOSTRUCTS_H
#include <string>

namespace kryuchkova
{
  struct Delimiter
  {
    char exp;
  };

  struct DblSci
  {
    double & ref;
  };

  struct UllOct
  {
    unsigned long long & ref;
  };

  struct String
  {
    std::string & ref;
  };

  struct Label
  {
    std::string exp;
  };

  std::istream & operator>>(std::istream & in, Delimiter && dest);
  std::istream & operator>>(std::istream & in, Label && dest);
  std::istream & operator>>(std::istream & in, String && dest);
  std::istream & operator>>(std::istream & in, DblSci && dest);
  std::istream & operator>>(std::istream & in, UllOct && dest);
}

#endif
