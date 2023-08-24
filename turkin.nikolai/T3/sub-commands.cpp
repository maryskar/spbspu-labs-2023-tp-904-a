#include "sub-commands.hpp"

#include <algorithm>
#include <cstddef>
#include <numeric>

#include "area-calc.hpp"
#include "pred-comp.hpp"

turkin::ReturnType turkin::area_odd(data_t & data, std::istream &)
{
  std::vector< Polygon > temp;
  std::copy_if(data.begin(), data.end(), std::back_inserter(temp), isOdd());
  return ReturnType(std::accumulate(temp.cbegin(), temp.cend(), 0.0, calcArea));
}

turkin::ReturnType turkin::area_even(data_t & data, std::istream &)
{
  std::vector< Polygon > temp;
  std::copy_if(data.begin(), data.end(), std::back_inserter(temp), isEven());
  return ReturnType(std::accumulate(temp.cbegin(), temp.cend(), 0.0, calcArea));
}

turkin::ReturnType turkin::area_mean(data_t & data, std::istream &)
{
  return ReturnType(std::accumulate(data.cbegin(), data.cend(), 0.0, calcArea) / 2.0);
}

turkin::ReturnType turkin::area_vertexes(data_t & data, std::istream & in)
{
  std::size_t amount = 0;
  in >> amount;
  std::vector< Polygon > temp;
  std::copy_if(data.begin(), data.end(), std::back_inserter(temp), isNum(amount));
  return ReturnType(std::accumulate(temp.cbegin(), temp.cend(), 0.0, calcArea));
}

turkin::ReturnType turkin::min_area(data_t & data, std::istream &)
{
   double result = calcArea(0.0, *std::min_element(data.cbegin(), data.cend(), isAreaLess()));
   return ReturnType(result);
}

turkin::ReturnType turkin::min_vertexes(data_t & data, std::istream &)
{
  std::size_t result = std::min_element(data.cbegin(), data.cend(), isSizeLess())->points.size();
  return ReturnType(result);
}

turkin::ReturnType turkin::max_area(data_t & data, std::istream &)
{
  double result = calcArea(0.0, *std::min_element(data.cbegin(), data.cend(), isAreaGreater()));
  return ReturnType(result);
}

turkin::ReturnType turkin::max_vertexes(data_t & data, std::istream &)
{
  std::size_t result = std::max_element(data.cbegin(), data.cend(), isSizeGreater())->points.size();
  return ReturnType(result);
}

turkin::ReturnType turkin::count_odd(data_t & data, std::istream &)
{
  std::size_t result = std::count_if(data.cbegin(), data.cend(), isOdd());
  return ReturnType(result);
}

turkin::ReturnType turkin::count_even(data_t & data, std::istream &)
{
  std::size_t result = std::count_if(data.cbegin(), data.cend(), isEven());
  return ReturnType(result);
}

turkin::ReturnType turkin::count_vertexes(data_t & data, std::istream & in)
{
  std::size_t amount = 0;
  in >> amount;
  std::size_t result = std::count_if(data.cbegin(), data.cend(), isNum(amount));
  return ReturnType(result);
}

turkin::ReturnType turkin::maxseq_sub(data_t & data, std::istream & in)
{
  std::size_t amount = 0;
  in >> amount;
  std::vector< Polygon > temp;
  std::copy_if(data.begin(), data.end(), std::back_inserter(temp), isNum(amount));
  return ReturnType(std::accumulate(temp.cbegin(), temp.cend(), 0.0, calcArea));
}

turkin::ReturnType turkin::rightshapes_sub(data_t & data, std::istream & in)
{
  std::size_t amount = 0;
  in >> amount;
  std::vector< Polygon > temp;
  std::copy_if(data.begin(), data.end(), std::back_inserter(temp), isNum(amount));
  return ReturnType(std::accumulate(temp.cbegin(), temp.cend(), 0.0, calcArea));
}
