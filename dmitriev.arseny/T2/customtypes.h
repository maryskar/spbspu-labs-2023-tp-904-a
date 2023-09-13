#ifndef CUTOMTYPES_H
#define CUTOMTYPES_H

#include <iostream>//возможно слищком жирно

struct SeparatorIO
{
  char expected;
};

std::istream& operator>>(std::istream& inp, SeparatorIO&& data);
std::ostream& operator<<(std::ostream& inp, const SeparatorIO& data);

struct DoubleI
{
  double& value;
};

std::istream& operator>>(std::istream& inp, DoubleI&& data);

struct DoubleO
{
  const double& value;
};

std::ostream& operator<<(std::ostream& inp, const DoubleO& data);

struct LongLongI
{
  long long& value;
};

std::istream& operator>>(std::istream& inp, LongLongI&& data);

struct LongLongO
{
  const long long& value;
};

std::ostream& operator<<(std::ostream& inp, const LongLongO& data);


#endif
