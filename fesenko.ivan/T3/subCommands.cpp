#include "subCommands.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include "subFunctions.h"

fesenko::ReturnType fesenko::area_odd(data_t &data, std::istream &)
{
  std::vector< Polygon > temp;
  std::copy_if(data.cbegin(), data.cend(), std::back_inserter(temp), isOdd());
  return ReturnType(std::accumulate(temp.cbegin(), temp.cend(), 0.0, calcArea));
}

fesenko::ReturnType fesenko::area_even(data_t &data, std::istream &)
{
  std::vector< Polygon > temp;
  std::copy_if(data.cbegin(), data.cend(), std::back_inserter(temp), isEven());
  return ReturnType(std::accumulate(temp.cbegin(), temp.cend(), 0.0, calcArea));
}

fesenko::ReturnType fesenko::area_mean(data_t &data, std::istream &)
{
  if (data.empty()) {
    throw std::logic_error("Divide by zero");
  }
  return ReturnType(std::accumulate(data.cbegin(), data.cend(), 0.0, calcArea) / data.size());
}

fesenko::ReturnType fesenko::area_vertexes(data_t &data, std::istream &in)
{
  size_t number = 0;
  in >> number;
  if (number < 3) {
    throw std::logic_error("Invalid number");
  }
  std::vector< Polygon > temp;
  std::copy_if(data.cbegin(), data.cend(), std::back_inserter(temp), isNumber(number));
  return ReturnType(std::accumulate(temp.cbegin(), temp.cend(), 0.0, calcArea));
}

fesenko::ReturnType fesenko::max_area(data_t &data, std::istream &)
{
  return ReturnType(calcArea(0.0, *std::max_element(data.cbegin(), data.cend(), isAreaLess())));
}

fesenko::ReturnType fesenko::max_vertexes(data_t &data, std::istream &)
{
  return ReturnType(std::max_element(data.cbegin(), data.cend(), isSizeLess())->points.size());
}

fesenko::ReturnType fesenko::min_area(data_t &data, std::istream &)
{
  return ReturnType(calcArea(0.0, *std::min_element(data.cbegin(), data.cend(), isAreaLess())));
}

fesenko::ReturnType fesenko::min_vertexes(data_t &data, std::istream &)
{
  return ReturnType(std::min_element(data.cbegin(), data.cend(), isSizeLess())->points.size());
}

fesenko::ReturnType fesenko::count_odd(data_t &data, std::istream &)
{
  size_t result = std::count_if(data.cbegin(), data.cend(), isOdd());
  return ReturnType(result);
}

fesenko::ReturnType fesenko::count_even(data_t &data, std::istream &)
{
  size_t result = std::count_if(data.cbegin(), data.cend(), isEven());
  return ReturnType(result);
}

fesenko::ReturnType fesenko::count_vertexes(data_t &data, std::istream &in)
{
  size_t number = 0;
  in >> number;
  if (number < 3) {
    throw std::runtime_error("Invalid number");
  }
  size_t result = std::count_if(data.cbegin(), data.cend(), isNumber(number));
  return ReturnType(result);
}

fesenko::ReturnType fesenko::rects_sub(data_t &data, std::istream &)
{
  size_t result = std::count_if(data.cbegin(), data.cend(), isRect());
  return ReturnType(result);
}

fesenko::ReturnType fesenko::inframe_sub(data_t &data, std::istream &in)
{
  Polygon polygon;
  in >> polygon;
  Polygon polygonRect = createBoundingRect(polygon);
  Point polyBL = polygonRect.points[0];
  Point polyTR = polygonRect.points[2];
  Polygon dataRect = createBoundingRect(data);
  Point dataBL = dataRect.points[0];
  Point dataTR = dataRect.points[2];
  bool result = dataBL.x <= polyBL.x && dataBL.y <= polyBL.y && dataTR.x >= polyTR.x && dataTR.y >= polyTR.y;
  return ReturnType(result);
}
