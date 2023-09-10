#include "subCommands.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include "subFunctions.h"

fesenko::ReturnType fesenko::area_odd(data_t &data)
{
  std::vector< Polygon > temp;
  std::copy_if(data.cbegin(), data.cend(), std::back_inserter(temp), isOdd);
  return ReturnType(std::accumulate(temp.cbegin(), temp.cend(), 0.0, calcArea));
}

fesenko::ReturnType fesenko::area_even(data_t &data)
{
  std::vector< Polygon > temp;
  std::copy_if(data.cbegin(), data.cend(), std::back_inserter(temp), isEven);
  return ReturnType(std::accumulate(temp.cbegin(), temp.cend(), 0.0, calcArea));
}

fesenko::ReturnType fesenko::area_mean(data_t &data)
{
  if (data.empty()) {
    throw std::logic_error("Divide by zero");
  }
  return ReturnType(std::accumulate(data.cbegin(), data.cend(), 0.0, calcArea) / data.size());
}
