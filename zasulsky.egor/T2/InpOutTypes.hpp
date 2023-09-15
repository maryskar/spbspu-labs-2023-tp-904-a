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

std::istream& operator>>(std::istream& in, DelimiterIO&& ref);
std::ostream& operator<<(std::ostream& out, const DelimiterIO& data);
std::istream& operator>>(std::istream& in, DblIO&& ref);
std::istream& operator>>(std::istream& in, StringIO&& ref);
std::istream& operator>>(std::istream& in, SllIO&& ref);
std::istream& operator>>(std::istream& in, LabelIO&& ref);
std::string convertToSci(double a);
#endif
