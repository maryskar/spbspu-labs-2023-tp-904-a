#ifndef data_t_H
#define data_t_H

#include <iostream>
#include <iomanip>
#include <string>

struct dataStruct
{
  double key1;
  long long key2;
  std::string key3;
};

std::istream& operator>>(std::istream& in, dataStruct& dest);
std::ostream& operator<<(std::ostream& out, const dataStruct& dest);

bool compare(dataStruct& lhs, dataStruct& rhs);

#endif
