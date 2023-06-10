#include "convert_to_bin.h"

std::string tarasenko::convertToBin(unsigned long long num)
{
  std::string bin_num = "";
  while (num)
  {
    bin_num = (num % 2 ? "1" : "0") + bin_num;
    num /= 2;
  }
  return (bin_num == "0" ? "0b" : "0b0") + bin_num;
}
