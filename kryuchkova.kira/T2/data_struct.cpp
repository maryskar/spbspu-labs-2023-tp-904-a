#include "data_struct.h"
#include <cmath>
#include <iostream>
#include <string>
#include <iomanip>
#include "iofmtguard.h"
#include "IOstructs.h"

namespace kryuchkova
{
  bool CmpData(const DataStruct & lhs, const DataStruct & rhs)
  {
    if (lhs.key1 != rhs.key1)
    {
      return lhs.key1 < rhs.key1;
    }
    else if (lhs.key2 != rhs.key2)
    {
      return lhs.key2 < rhs.key2;
    }
    else
    {
      return lhs.key3.size() < rhs.key3.size();
    }
  }

  std::string convertToSci(double data)
  {
    int n = 0;
    while (std::abs(data) >= 10)
    {
      data /= 10;
      ++n;
    }
    while (std::abs(data) < 1)
    {
      data *= 10;
      --n;
    }
    data *= 10;
    int val = std::round(data);
    std::string res = std::to_string(val);
    res.insert(1ull, 1ull, '.');
    res += 'e';
    if (n >= 0)
    {
      res += '+';
    }
    res += std::to_string(n);
    return res;
  }
}