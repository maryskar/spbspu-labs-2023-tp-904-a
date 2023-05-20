#include "convert_to_bin.h"

unsigned long long tarasenko::convertToBin(unsigned long long num)
{
  unsigned long long bin_num = 0;
  unsigned long long k = 1;
  while (num)
  {
    bin_num += (num % 2) * k;
    k *= 10;
    num /= 2;
  }
  return bin_num;
}
