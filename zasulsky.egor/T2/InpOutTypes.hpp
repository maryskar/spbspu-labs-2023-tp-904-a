#ifndef INPOUTTYPES_HPP
#define INPOUTTYPES_HPP

#include <iostream>
#include <string>
#include <cmath>

struct DelimiterIO
{
  char exp;
};

struct LabelIO
{
  std::string exp;
};

struct DblIO
{
  double& ref;
};

struct StringIO
{
  std::string& ref;
};

struct SllIO
{
  long long& ref;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, LabelIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, LongLongIO&& dest);
std::istream& operator>>(std::istream& in, DoubleI&& dest);
std::ostream& operator<<(std::ostream& out, const DoubleO&& dest);
std::string convertToSci(double a);
#endif
