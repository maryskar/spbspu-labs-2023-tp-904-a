#include "commands.h"
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <functional>
#include <streamguard.h>

namespace
{
  using namespace std::placeholders;
  auto getSizeL = std::bind(dmitriev::getSize, _1);
  auto getSizeR = std::bind(dmitriev::getSize, _2);
  auto getAreaL = std::bind(dmitriev::getArea, _1);
  auto getAreaR = std::bind(dmitriev::getArea, _2);
  auto isOdd = std::bind(std::modulus< size_t >{}, getSizeL, 2);
  auto isEven = std::bind(std::logical_not< bool >{}, std::bind(isOdd, _1));
  auto isSizeEqualToN = std::bind(std::equal_to< size_t >{}, getSizeL, _2);
  auto countAreas = std::bind(std::plus< double >{}, _1, getAreaR);
}

using predicate = std::function< bool(const polygon&) >;
using comparator = std::function< bool(const polygon&, const polygon&) >;

void printArea(const polygons& data, predicate pred, std::ostream& out)
{
  polygons areas;
  std::copy_if(data.cbegin(), data.cend(), std::back_inserter(areas), pred);

  dmitriev::StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(areas.begin(), areas.end(), 0.0, countAreas);
}

void dmitriev::printEvenArea(const polygons& data, std::ostream& out)
{
  printArea(data, isEven, out);
}

void dmitriev::printOddArea(const polygons& data, std::ostream& out)
{
  printArea(data, isOdd, out);
}

void dmitriev::printNSizeArea(const polygons& data, size_t number, std::ostream& out)
{
  if (number < 3)
  {
    throw std::invalid_argument("Invalid command parameter");
  }
  using namespace std::placeholders;
  printArea(data, std::bind(isSizeEqualToN, _1, number), out);
}

void dmitriev::printMeanArea(const polygons& data, std::ostream& out)
{
  if (data.empty())
  {
    throw std::invalid_argument("empty dataset");
  }
  dmitriev::StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(data.begin(), data.end(), 0.0, countAreas) / data.size();
}

void printMaxMinArea(const polygons& data, comparator cmp, std::ostream& out)
{
  if (data.empty())
  {
    throw std::invalid_argument("empty data");
  }

  dmitriev::StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << dmitriev::getArea(*(std::max_element(data.begin(), data.end(), cmp)));
}

void dmitriev::printMaxArea(const polygons& data, std::ostream& out)
{
  auto isGreater = std::bind(std::less< double >{}, getAreaL, getAreaR);

  printMaxMinArea(data, isGreater, out);
}

void dmitriev::printMinArea(const polygons& data, std::ostream& out)
{
  auto isLess = std::bind(std::greater< double >{}, getAreaL, getAreaR);

  printMaxMinArea(data, isLess, out);
}

void printSize(const polygons& data, comparator cmp, std::ostream& out)
{
  if (data.empty())
  {
    throw std::invalid_argument("empty data");
  }

  out << dmitriev::getSize(*(std::max_element(data.begin(), data.end(), cmp)));
}

void dmitriev::printMaxSize(const polygons& data, std::ostream& out)
{
  auto isGreater = std::bind(std::less< size_t >{}, getSizeL, getSizeR);

  printSize(data, isGreater, out);
}

void dmitriev::printMinSize(const polygons& data, std::ostream& out)
{
  auto isLess = std::bind(std::greater< size_t >{}, getSizeL, getSizeR);

  printSize(data, isLess, out);
}

void printSizeCount(const polygons& data, predicate pred, std::ostream& out)
{
  out << std::count_if(data.begin(), data.end(), pred);
}

void dmitriev::printEvenSizeCount(const polygons& data, std::ostream& out)
{
  printSizeCount(data, isEven, out);
}

void dmitriev::printOddSizeCount(const polygons& data, std::ostream & out)
{
  printSizeCount(data, isOdd, out);
}

void dmitriev::printNSizeCount(const polygons& data, size_t number, std::ostream & out)
{
  if (number < 3)
  {
    throw std::invalid_argument("Invalid command parameter");
  }
  using namespace std::placeholders;
  printSizeCount(data, std::bind(isSizeEqualToN, _1, number), out);
}

void printBool(std::ostream& out, bool value)
{
  if (value)
  {
    out << "<TRUE>";
  }
  else
  {
    out << "<FALSE>";
  }
}

void dmitriev::printInFrame(const polygons& data, const polygon& figure, std::ostream& out)
{
  if (data.empty())
  {
    throw std::invalid_argument("empty data");
  }

  printBool(out, isFrameInFrame(getFrame(figure), getPolygonsFrame(data)));
}

void dmitriev::printSame(const polygons& data, const polygon& figure, std::ostream& out)
{
  if (data.empty())
  {
    throw std::invalid_argument("empty data");
  }
  out << dmitriev::countAllSame(data, figure);
}
