#include "convert_to_bin.hpp"

std::string zhuravlev::convertToBin(unsigned long long value)
{
  std::string result = "";
  while (value != 0)
  {
    result += value % 2 ? "1" : "0";
    value /= 2;
  }
  return (result == "0" ? "0b" : "0b0") + result;
}
