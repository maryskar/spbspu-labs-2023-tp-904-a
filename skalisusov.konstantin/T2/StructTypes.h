#ifndef SPBSPU_LABS_2023_TP_904_A_STRUCTTYPES_H
#define SPBSPU_LABS_2023_TP_904_A_STRUCTTYPES_H
#include <string>

namespace skalisusov
{
  struct LabelIO
  {
    std::string label_;
  };
  struct DelimiterIO
  {
    char exp_;
  };
  struct StringIO
  {
    std::string &str_;
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
    const double dubscienO_;
  };
  std::istream & operator>>(std::istream &in, LabelIO &&dest);
  std::istream & operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream & operator>>(std::istream &in, DoubleLiteralFormatIO &&dest);
  std::istream & operator>>(std::istream &in, DoubleSciencificFormatI &&dest);
  std::ostream & operator<<(std::ostream &out, const DoubleSciencificFormatO &dest);
  std::istream & operator>>(std::istream &in, StringIO &&dest);
}

#endif //SPBSPU_LABS_2023_TP_904_A_STRUCTTYPES_H
