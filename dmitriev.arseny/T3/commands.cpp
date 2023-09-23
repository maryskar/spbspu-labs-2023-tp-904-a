#include "commands.h"
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <functional>
#include <streamguard.h>

namespace
{
  using namespace std::placeholders;
  auto getSize = std::bind(dmitriev::getSize, _1);
  auto getSizeL = std::bind(getSize, _1);
  auto getSizeR = std::bind(getSize, _2);
  auto getArea = std::bind(dmitriev::getArea, _1);
  auto getAreaL = std::bind(getArea, _1);
  auto getAreaR = std::bind(getArea, _2);
  auto isEven = std::bind(std::modulus< size_t >{}, getSize, 2);
  auto isOdd = std::bind(std::logical_not< bool >{}, std::bind(isEven, _1));
  auto isSizeEqualToN = std::bind(std::equal_to< size_t >{}, getSize, _2);
  auto countAreas = std::bind(std::plus< double >{}, _1, getAreaR);
}

using predicate = std::function< bool(const polygon&) >;
using comparator = std::function< bool(const polygon&, const polygon&) >;

void printArea(polygons data, predicate condition, std::ostream& out)
{
  polygons areas;
  std::copy_if(data.cbegin(), data.cend(), std::back_inserter(areas), condition);

  dmitriev::StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(areas.begin(), areas.end(), 0.0, countAreas) << '\n';
}

void dmitriev::printEvenArea(polygons data, std::ostream& out)
{
  printArea(data, isEven, out);
}

void dmitriev::printOddArea(polygons data, std::ostream& out)
{
  printArea(data, isOdd, out);
}

void dmitriev::printNSizeArea(polygons data, size_t number, std::ostream& out)
{
  printArea(data, std::bind(isSizeEqualToN, _1, number), out);
}

void dmitriev::printMeanArea(polygons data, std::ostream& out)
{
  dmitriev::StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(data.begin(), data.end(), 0.0, countAreas) / data.size() << '\n';
}

void printMaxMinArea(polygons data, comparator cmp, std::ostream& out)
{
  dmitriev::StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << dmitriev::getArea(*(std::max_element(data.begin(), data.end(), cmp))) << '\n';
}

void dmitriev::printMaxArea(polygons data, std::ostream& out)
{
  auto isGreater = std::bind(std::less< double >{}, getAreaL, getAreaR);

  printMaxMinArea(data, isGreater, out);
}

void dmitriev::printMinArea(polygons data, std::ostream& out)
{
  auto isLess = std::bind(std::greater< double >{}, getAreaL, getAreaR);

  printMaxMinArea(data, isLess, out);
}

void printSize(polygons data, comparator cmp, std::ostream& out)
{
  out << dmitriev::getSize(*(std::max_element(data.begin(), data.end(), cmp))) << '\n';
}

void dmitriev::printMaxSize(polygons data, std::ostream& out)
{
  auto isGreater = std::bind(std::less< size_t >{}, getSizeL, getSizeR);

  printSize(data, isGreater, out);
}

void dmitriev::printMinSize(polygons data, std::ostream& out)
{
  auto isLess = std::bind(std::greater< size_t >{}, getSizeL, getSizeR);

  printSize(data, isLess, out);
}

void printSizeCount(polygons data, predicate pred, std::ostream& out)
{
  out << std::count_if(data.begin(), data.end(), pred) << '\n';
}

void dmitriev::printEvenSizeCount(polygons data, std::ostream& out)
{
  printSizeCount(data, isEven, out);
}

void dmitriev::printOddSizeCount(polygons data, std::ostream & out)
{
  printSizeCount(data, isOdd, out);
}

void dmitriev::printNSizeCount(polygons data, size_t number, std::ostream & out)
{
  printSizeCount(data, std::bind(isSizeEqualToN, _1, number), out);
}
