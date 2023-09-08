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

  struct Label
  {
    std::string exp;
  };
}

#endif
