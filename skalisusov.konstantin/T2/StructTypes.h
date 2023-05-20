#ifndef SPBSPU_LABS_2023_TP_904_A_STRUCTTYPES_H
#define SPBSPU_LABS_2023_TP_904_A_STRUCTTYPES_H

#include <sstream>
#include <string>
#include <cassert>
#include <iomanip>

namespace skalisusov
{
  struct CoverIO
  {
    std::string cover_;
  };
  struct DelimiterIO
  {
    char exp;
  };

  struct DoubleLiteralFormatIO
  {
    double &dublit_;
  };
  struct DoubleSciencificFormatI
  {
    double &dubscienI_;
  };
  struct DoubleSciencificFormatO
  {
    const double &dubscienO_;
  };
  struct StringIO
  {
    std::string &str_;
  };
}

#endif //SPBSPU_LABS_2023_TP_904_A_STRUCTTYPES_H
