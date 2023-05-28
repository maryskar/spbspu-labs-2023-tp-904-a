#ifndef T2_COMPARE_HPP
#define T2_COMPARE_HPP
#include "DataStruct.hpp"
namespace litvin
{
  struct Compare
  {
    bool operator()(const DataStruct & data1, const DataStruct & data2) const;
  };
}
#endif

