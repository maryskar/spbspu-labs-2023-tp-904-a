#ifndef data_t_H
#define data_t_H

#include <string>
#include <iostream>
#include <iomanip>

struct dataStruct
{
  double key1;
  long long key2;
  std::string key3;
};

std::istream& operator>>(std::istream& in, dataStruct& ref);
std::ostream& operator<<(std::ostream& out, const dataStruct& ref);

bool compare(dataStruct& lhs, dataStruct& rhs);

#endif
