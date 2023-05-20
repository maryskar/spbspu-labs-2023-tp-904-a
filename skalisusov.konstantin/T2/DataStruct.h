#ifndef SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
#define SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

namespace skalisusov
{
  struct Data: public std::__1::error_code
  {
    double key1;
    double key2;
    std::string key3;
  };
  struct DoubleScientificFormatI
  {
    double &scien_;
  };

  struct DoubleScientificFormatO
  {
    const double scien_;
  };

  struct DoubleLiteralFormatIO
  {
    double &real_;
  };
  struct StringIO
  {
    std::string &str;
  };

  struct DelimiterIO
  {
    char exp_;
  };

  struct CoverIO
  {
    std::string exp;
  };

  std::istream &operator>>(std::istream &in, DoubleLiteralFormatIO &&dest);
  std::istream &operator>>(std::istream &in, DoubleScientificFormatI &&dest);
  std::ostream &operator<<(std::ostream &out, DoubleScientificFormatO);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, CoverIO &&dest);
  std::istream &operator>>(std::istream &in, Data &dest);
  std::ostream &operator<<(std::ostream &out, Data &src);


}
#endif //SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
