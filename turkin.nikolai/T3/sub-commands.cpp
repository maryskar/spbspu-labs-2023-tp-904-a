#include "sub-commands.hpp"

#include <algorithm>
#include <functional>
#include <cstddef>
#include <numeric>
#include <stdexcept>
#include <string>

#include "area-calc.hpp"
#include "data-structs.hpp"
#include "pred-comp.hpp"

turkin::ReturnType turkin::area_odd(data_t & data, std::string &)
{
  std::vector< Polygon > temp;
  std::copy_if(data.begin(), data.end(), std::back_inserter(temp), isOdd());
  return ReturnType(std::accumulate(temp.cbegin(), temp.cend(), 0.0, calcArea));
}

turkin::ReturnType turkin::area_even(data_t & data, std::string &)
{
  std::vector< Polygon > temp;
  std::copy_if(data.begin(), data.end(), std::back_inserter(temp), isEven());
  return ReturnType(std::accumulate(temp.cbegin(), temp.cend(), 0.0, calcArea));
}

turkin::ReturnType turkin::area_mean(data_t & data, std::string &)
{
  if (data.empty())
  {
    throw std::runtime_error("empty source");
  }
  return ReturnType(std::accumulate(data.cbegin(), data.cend(), 0.0, calcArea) / data.size());
}

turkin::ReturnType turkin::area_vertexes(data_t & data, std::string & in)
{
  std::size_t amount = std::stoull(in);
  if (amount < 3)
  {
    throw std::runtime_error("bad input");
  }
  std::vector< Polygon > temp;
  std::copy_if(data.begin(), data.end(), std::back_inserter(temp), isNum(amount));
  return ReturnType(std::accumulate(temp.cbegin(), temp.cend(), 0.0, calcArea));
}

turkin::ReturnType turkin::min_area(data_t & data, std::string &)
{
  double result = calcArea(0.0, *std::min_element(data.cbegin(), data.cend(), isAreaLess()));
  return ReturnType(result);
}

turkin::ReturnType turkin::min_vertexes(data_t & data, std::string &)
{
  std::size_t result = std::min_element(data.cbegin(), data.cend(), isSizeGreater())->points.size();
  return ReturnType(result);
}

turkin::ReturnType turkin::max_area(data_t & data, std::string &)
{
  double result = calcArea(0.0, *std::min_element(data.cbegin(), data.cend(), isAreaGreater()));
  return ReturnType(result);
}

turkin::ReturnType turkin::max_vertexes(data_t & data, std::string &)
{
  std::size_t result = std::max_element(data.cbegin(), data.cend(), isSizeLess())->points.size();
  return ReturnType(result);
}

turkin::ReturnType turkin::count_odd(data_t & data, std::string &)
{
  std::size_t result = std::count_if(data.cbegin(), data.cend(), isOdd());
  return ReturnType(result);
}

turkin::ReturnType turkin::count_even(data_t & data, std::string &)
{
  std::size_t result = std::count_if(data.cbegin(), data.cend(), isEven());
  return ReturnType(result);
}

turkin::ReturnType turkin::count_vertexes(data_t & data, std::string & in)
{
  std::size_t amount = std::stoull(in);
  if (amount < 3)
  {
    throw std::runtime_error("bad input");
  }
  std::size_t result = std::count_if(data.cbegin(), data.cend(), isNum(amount));
  return ReturnType(result);
}

turkin::ReturnType turkin::maxseq_sub(data_t & data, std::string & in)
{
  Polygon temp;
  in >> temp;
  std::size_t amount = 0;
  using namespace std::placeholders;
  auto pred = std::bind(std::equal_to< Polygon >{}, _1, temp);
  std::deque< Polygon >::iterator first = data.begin();
  while (first != data.end())
  {
    first = std::find_if(first, data.end(), pred);
    std::deque< Polygon >::iterator last = std::find_if_not(first, data.end(), pred);
    amount = std::max(amount, static_cast< size_t >(std::abs(std::distance(first, last))));
    first = last;
  }
  if (amount == 0)
  {
    throw std::runtime_error("bad input");
  }
  return ReturnType(amount);
}

turkin::ReturnType turkin::rightshapes_sub(data_t & data, std::string &)
{
  std::size_t result = std::count_if(data.begin(), data.end(), isRightAngle());
  return ReturnType(result);
}
