#include "commands.h"
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <functional>
#include <streamguard.h>

using namespace std::placeholders;
auto getSize = std::bind(dmitriev::getSize, _1);
auto getArea = std::bind(dmitriev::getArea, _1);
auto isEven = std::bind(std::modulus< size_t >{}, getSize, 2);
auto isOdd = std::bind(std::logical_not< bool >{}, std::bind(isEven, _1));
auto isSizeEqualToN = std::bind(std::equal_to< size_t >{}, getSize, _2);
auto isGreaterSize = std::bind(std::greater< size_t >{}, getSize, getSize);
auto isGreaterArea = std::bind(std::less< double >{}, std::bind(getArea, _1), std::bind(getArea, _2));
auto isLessArea = std::bind(std::greater< double >{}, std::bind(getArea, _1), std::bind(getArea, _2));

double countAreas(double result, const dmitriev::Polygon& polygon)
{
  return result + dmitriev::getArea(polygon);
}

void printArea(std::vector< dmitriev::Polygon > data,
  std::function< bool(const dmitriev::Polygon&) > condition,
  std::ostream& out)
{
  std::vector< dmitriev::Polygon > areas;
  std::copy_if(data.cbegin(), data.cend(), std::back_inserter(areas), condition);

  dmitriev::StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(areas.begin(), areas.end(), 0.0, countAreas) << '\n';
}

void dmitriev::printEvenArea(std::vector< Polygon > data, std::ostream& out)
{
  printArea(data, isEven, out);
}

void dmitriev::printOddArea(std::vector< Polygon > data, std::ostream& out)
{
  printArea(data, isOdd, out);
}

void dmitriev::printNSizeArea(std::vector< Polygon > data, size_t number, std::ostream& out)
{
  printArea(data, std::bind(isSizeEqualToN, _1, number), out);
}

void dmitriev::printMeanArea(std::vector< Polygon > data, std::ostream& out)
{
  dmitriev::StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(data.begin(), data.end(), 0.0, countAreas) / data.size() << '\n';
}

void printMaxMinArea(std::vector< dmitriev::Polygon > data,
  std::function< bool(const dmitriev::Polygon&, const dmitriev::Polygon&) > comparator,
  std::ostream& out)
{
  dmitriev::StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << dmitriev::getArea(*(std::max_element(data.begin(), data.end(), comparator))) << '\n';
}

void dmitriev::printMaxArea(std::vector< Polygon > data, std::ostream& out)
{
  printMaxMinArea(data, isGreaterArea, out);
}

void dmitriev::printMinArea(std::vector< Polygon > data, std::ostream& out)
{
  printMaxMinArea(data, isLessArea, out);
}
