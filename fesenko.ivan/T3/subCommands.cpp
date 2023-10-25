#include "subCommands.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <iterator>
#include "subFunctions.h"
#include "returnType.h"

std::ostream &fesenko::area_vertexes(const data_t &data, size_t number, std::ostream &out)
{
  if (number < 3) {
    throw std::logic_error("Invalid number");
  }
  std::vector< Polygon > temp;
  std::copy_if(data.cbegin(), data.cend(), std::back_inserter(temp), isNumber(number));
  double result = std::accumulate(temp.cbegin(), temp.cend(), 0.0, calcArea);
  return out << ReturnType(result);
}

std::ostream &fesenko::count_vertexes(const data_t &data, size_t number, std::ostream &out)
{
  if (number < 3) {
    throw std::runtime_error("Invalid number");
  }
  size_t result = std::count_if(data.cbegin(), data.cend(), isNumber(number));
  return out << ReturnType(result);
}

std::ostream &fesenko::area_odd(const data_t &data, std::ostream &out)
{
  std::vector< Polygon > temp;
  std::copy_if(data.cbegin(), data.cend(), std::back_inserter(temp), isOdd());
  double result = std::accumulate(temp.cbegin(), temp.cend(), 0.0, calcArea);
  return out << ReturnType(result);
}

std::ostream &fesenko::area_even(const data_t &data, std::ostream &out)
{
  std::vector< Polygon > temp;
  std::copy_if(data.cbegin(), data.cend(), std::back_inserter(temp), isEven());
  double result = std::accumulate(temp.cbegin(), temp.cend(), 0.0, calcArea);
  return out << ReturnType(result);
}

std::ostream &fesenko::area_mean(const data_t &data, std::ostream &out)
{
  if (data.empty()) {
    throw std::logic_error("Divide by zero");
  }
  double result = std::accumulate(data.cbegin(), data.cend(), 0.0, calcArea) / data.size();
  return out << ReturnType(result);
}

std::ostream &fesenko::max_area(const data_t &data, std::ostream &out)
{
  if (data.empty()) {
    throw std::logic_error("Data is empty");
  }
  double result = calcArea(0.0, *std::max_element(data.cbegin(), data.cend(), isAreaLess()));
  return out << ReturnType(result);
}

std::ostream &fesenko::max_vertexes(const data_t &data, std::ostream &out)
{
  if (data.empty()) {
    throw std::logic_error("Data is empty");
  }
  size_t result = std::max_element(data.cbegin(), data.cend(), isSizeLess())->points.size();
  return out << ReturnType(result);
}

std::ostream &fesenko::min_area(const data_t &data, std::ostream &out)
{
  if (data.empty()) {
    throw std::logic_error("Data is empty");
  }
  double result = calcArea(0.0, *std::min_element(data.cbegin(), data.cend(), isAreaLess()));
  return out << ReturnType(result);
}

std::ostream &fesenko::min_vertexes(const data_t &data, std::ostream &out)
{
  if (data.empty()) {
    throw std::logic_error("Data is empty");
  }
  size_t result = std::min_element(data.cbegin(), data.cend(), isSizeLess())->points.size();
  return out << ReturnType(result);
}

std::ostream &fesenko::count_odd(const data_t &data, std::ostream &out)
{
  size_t result = std::count_if(data.cbegin(), data.cend(), isOdd());
  return out << ReturnType(result);
}

std::ostream &fesenko::count_even(const data_t &data, std::ostream &out)
{
  size_t result = std::count_if(data.cbegin(), data.cend(), isEven());
  return out << ReturnType(result);
}

std::ostream &fesenko::rects(const data_t &data, std::ostream &out)
{
  size_t result = std::count_if(data.cbegin(), data.cend(), isRect());
  return out << ReturnType(result);
}

std::ostream &fesenko::inframe(const data_t &data, std::istream &in, std::ostream &out)
{
  Polygon polygon;
  in >> polygon;
  if (!in) {
    throw std::invalid_argument("Incorrect polygon");
  }
  Polygon polygonRect = createBoundingRect(polygon);
  Point polyBL = polygonRect.points[0];
  Point polyTR = polygonRect.points[2];
  Polygon dataRect = createBoundingRect(data);
  Point dataBL = dataRect.points[0];
  Point dataTR = dataRect.points[2];
  bool result = dataBL.x <= polyBL.x && dataBL.y <= polyBL.y && dataTR.x >= polyTR.x && dataTR.y >= polyTR.y;
  return out << ReturnType(result);
}
