#include "sort.h"

bool T2::compareData(const T2::DataStruct &lhs, const T2::DataStruct &rhs)
{
  if (rhs.key1 > lhs.key1) {
    return true;
  }
  else if ((lhs.key1 == rhs.key1) && compareRational(rhs.key2, lhs.key2)) {
    return true;
  }
  else if ((lhs.key1 == rhs.key1) && rationalEqual(lhs.key2, rhs.key2) && rhs.key3.size() >= lhs.key3.size()) {
    return true;
  }
  else {
    return false;
  }
}

bool T2::compareRational(const std::pair< long long int, unsigned long long int > &lhs,
                         const std::pair< long long int, unsigned long long int > &rhs)
{
  return lhs.first / lhs.second > rhs.first / rhs.second;
}

bool T2::rationalEqual(const std::pair< long long int, unsigned long long int > &lhs,
                       const std::pair< long long int, unsigned long long int > &rhs)
{
  return lhs.first / lhs.second == rhs.first / rhs.second;
}
