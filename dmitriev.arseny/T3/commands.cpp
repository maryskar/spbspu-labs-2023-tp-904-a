#include "commands.h"
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <functional>
#include <streamguard.h>

using namespace std::placeholders;
auto getSize = std::bind(dmitriev::getSize, _1);
auto isEven = std::bind(std::modulus< size_t >{}, getSize, 2);
auto isOdd = std::bind(std::logical_not< bool >{}, std::bind(isEven, _1));
auto isSizeEqualToN = std::bind(std::equal_to< size_t >{}, getSize, _2);

double countAreas(double result, const dmitriev::Polygon& polygon)
{
  return result + dmitriev::getArea(polygon);
}

void dmitriev::printEvenArea(std::ostream& out, std::vector< Polygon > data)
{
  std::vector< Polygon > areas;
  std::copy_if(data.cbegin(), data.cend(), std::back_inserter(areas), isEven);
  
  dmitriev::StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(areas.begin(), areas.end(), 0.0, countAreas) << '\n';
}

void dmitriev::printOddArea(std::ostream& out, std::vector< Polygon > data)
{
  std::vector< Polygon > areas;
  std::copy_if(data.cbegin(), data.cend(), std::back_inserter(areas), isOdd);

  dmitriev::StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(areas.begin(), areas.end(), 0.0, countAreas) << '\n';
}

void dmitriev::printNSizeArea(std::ostream& out, std::vector< Polygon > data, size_t number)
{
  std::vector< Polygon > areas;
  std::copy_if(data.cbegin(),
    data.cend(),
    std::back_inserter(areas),
    std::bind(isSizeEqualToN, _1, number));

  dmitriev::StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(areas.begin(), areas.end(), 0.0, countAreas) << '\n';
}

void dmitriev::printMeanArea(std::ostream& out, std::vector< Polygon > data)
{
  dmitriev::StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(data.begin(), data.end(), 0.0, countAreas) / data.size() << '\n';
}
