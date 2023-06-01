#ifndef T2_DATASTRUCT_HPP
#define T2_DATASTRUCT_HPP
#include "ScopeGuard.hpp"
#include "structures.hpp"
namespace litvin
{
  struct DataStruct
  {
    double key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };
  std::istream & operator>>(std::istream & in, DataStruct & dest);
  std::ostream & operator<<(std::ostream & out, const DataStruct & dest);
}
#endif
