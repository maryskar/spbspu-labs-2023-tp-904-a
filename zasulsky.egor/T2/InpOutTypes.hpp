#ifndef INPOUTTYPES_HPP
#define INPOUTTYPES_HPP

#include <string>
#include <iostream>

namespace zasulsky
{
  struct DelimiterIO
  {
    char exp;
  };
  struct DblI
  {
    double& num;
  };
  struct DblO
  {
    const double num;
  };
  struct SllIO
  {
    long long& num;
  };
  struct StringIO
  {
    std::string& exp;
  };
  struct LabelIO
  {
    std::string exp;
  };
  std::istream& operator>>(std::istream& in, DelimiterIO&& obj);
  std::istream& operator>>(std::istream& in, LabelIO&& obj);
  std::istream& operator>>(std::istream& in, StringIO&& obj);
  std::istream& operator>>(std::istream& in, SllIO&& obj);
  std::istream& operator>>(std::istream& in, DblI&& obj);
  std::ostream& operator<<(std::ostream& out, const DblO&& obj);
}
#endif
