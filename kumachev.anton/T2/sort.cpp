#include "sort.h"

bool kumachev::compareData(const kumachev::DataStruct &lhs, const kumachev::DataStruct &rhs)
{
  if (rhs.key1 > lhs.key1) {
    return true;
  }
  else if ((lhs.key1 == rhs.key1) && compareRational(rhs.key2, lhs.key2) > 0) {
    return true;
  }
  else if ((lhs.key1 == rhs.key1) && compareRational(lhs.key2, rhs.key2) == 0 && rhs.key3.size() >= lhs.key3.size()) {
    return true;
  }
  else {
    return false;
  }
}

int kumachev::compareRational(const std::pair< long long int, unsigned long long int > &lhs,
    const std::pair< long long int, unsigned long long int > &rhs)
{
  auto diff = static_cast<float>(lhs.first) / lhs.second - static_cast<float>(rhs.first) / rhs.second;

  if (diff < 0) {
    return -1;
  }
  else if (diff > 0) {
    return 1;
  }
  else {
    return 0;
  }
}
