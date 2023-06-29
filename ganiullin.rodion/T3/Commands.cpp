#include "Commands.h"

#include <algorithm>
#include <functional>
#include <iomanip>
#include <numeric>
#include <stdexcept>
#include "FormatGuard.h"
#include "TypesIO.h"

namespace {
  using OutS = std::ostream;
  using InS = std::istream;
  using namespace std::placeholders;
  using PolyVector = std::vector< ganiullin::Polygon >;

  const auto getNumOfVertexes = std::bind(ganiullin::getNumOfVertexes, _1);
  const auto getNumOfVertModTwo = std::bind(std::modulus< size_t >{}, getNumOfVertexes, 2);

  const auto hasEvenVertexes = std::bind(std::equal_to< size_t >{}, getNumOfVertModTwo, 0);
  const auto hasOddVertexes = std::bind(std::logical_not< bool >{}, hasEvenVertexes);
  const auto hasVertexesEqualTo = std::bind(std::equal_to< size_t >{}, getNumOfVertexes, _2);

  double processAreaEven(const PolyVector& polygons)
  {
    PolyVector filteredPolygons;
    std::vector< double > areas;

    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto filteredInsertIt = std::back_inserter(filteredPolygons);

    std::copy_if(polygonsBeginIt, polygonsEndIt, filteredInsertIt, hasEvenVertexes);
    areas.reserve(filteredPolygons.size());

    auto filterBeginIt = std::begin(filteredPolygons);
    auto filterEndIt = std::end(filteredPolygons);
    auto areasInsertIt = std::back_inserter(areas);

    std::transform(filterBeginIt, filterEndIt, areasInsertIt, ganiullin::getArea);

    return std::accumulate(std::begin(areas), std::end(areas), 0.0);
  }
  double processAreaOdd(const PolyVector& polygons)
  {
    PolyVector filteredPolygons;
    std::vector< double > areas;

    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto filteredInsertIt = std::back_inserter(filteredPolygons);

    std::copy_if(polygonsBeginIt, polygonsEndIt, filteredInsertIt, hasOddVertexes);
    areas.reserve(filteredPolygons.size());

    auto filterBeginIt = std::begin(filteredPolygons);
    auto filterEndIt = std::end(filteredPolygons);
    auto areasInsertIt = std::back_inserter(areas);

    std::transform(filterBeginIt, filterEndIt, areasInsertIt, ganiullin::getArea);
    auto areasBeginIt = std::begin(areas);
    auto areasEndIt = std::end(areas);

    return std::accumulate(areasBeginIt, areasEndIt, 0.0);
  }
  double processAreaMean(const PolyVector& polygons)
  {
    if (polygons.size() == 0) {
      throw std::logic_error("Polygons vector should not be empty");
    }
    std::vector< double > areas;
    areas.reserve(polygons.size());

    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto areasInsertIt = std::back_inserter(areas);

    std::transform(polygonsBeginIt, polygonsEndIt, areasInsertIt, ganiullin::getArea);
    auto areasBeginIt = std::begin(areas);
    auto areasEndIt = std::end(areas);

    return std::accumulate(areasBeginIt, areasEndIt, 0.0) / polygons.size();
  }
  double processAreaVertexNum(const PolyVector& polygons, size_t vertexNum)
  {
    PolyVector filteredPolygons;
    std::vector< double > areas;

    auto polyBeginIt = std::begin(polygons);
    auto polyEndIt = std::end(polygons);
    auto filteredInsertIt = std::back_inserter(filteredPolygons);

    std::copy_if(polyBeginIt, polyEndIt, filteredInsertIt, std::bind(hasVertexesEqualTo, _1, vertexNum));
    areas.reserve(filteredPolygons.size());

    auto filterBeginIt = std::begin(filteredPolygons);
    auto filterEndIt = std::end(filteredPolygons);
    auto areasInsertIt = std::back_inserter(areas);

    std::transform(filterBeginIt, filterEndIt, areasInsertIt, ganiullin::getArea);

    auto areasBeginIt = std::begin(areas);
    auto areasEndIt = std::end(areas);

    return std::accumulate(areasBeginIt, areasEndIt, 0.0);
  }

  double processMaxArea(const PolyVector& polygons)
  {
    if (polygons.size() == 0) {
      throw std::logic_error("Polygons vector should not be empty");
    }
    std::vector< double > areas;
    areas.reserve(polygons.size());

    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto areasInsertIt = std::back_inserter(areas);

    std::transform(polygonsBeginIt, polygonsEndIt, areasInsertIt, ganiullin::getArea);

    auto areasBeginIt = std::begin(areas);
    auto areasEndIt = std::end(areas);

    return (*std::max_element(areasBeginIt, areasEndIt));
  }
  size_t processMaxVertexNum(const PolyVector& polygons)
  {
    if (polygons.size() == 0) {
      throw std::logic_error("Polygons vector should not be empty");
    }
    std::vector< size_t > numVertexes;
    numVertexes.reserve(polygons.size());

    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto vertexInsertIt = std::back_inserter(numVertexes);

    std::transform(polygonsBeginIt, polygonsEndIt, vertexInsertIt, ganiullin::getNumOfVertexes);

    auto vertexBeginIt = std::begin(numVertexes);
    auto vertexEndIt = std::end(numVertexes);

    return (*std::max_element(vertexBeginIt, vertexEndIt));
  }

  double processMinArea(const PolyVector& polygons)
  {
    if (polygons.size() == 0) {
      throw std::logic_error("Polygons vector should not be empty");
    }
    std::vector< double > areas;
    areas.reserve(polygons.size());

    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto areasInsertIt = std::back_inserter(areas);

    std::transform(polygonsBeginIt, polygonsEndIt, areasInsertIt, ganiullin::getArea);

    auto areasBeginIt = std::begin(areas);
    auto areasEndIt = std::end(areas);

    return (*std::min_element(areasBeginIt, areasEndIt));
  }
  size_t processMinVertexNum(const PolyVector& polygons)
  {
    if (polygons.size() == 0) {
      throw std::logic_error("Polygons vector should not be empty");
    }
    std::vector< size_t > numVertexes;
    numVertexes.reserve(polygons.size());

    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto vertexInsertIt = std::back_inserter(numVertexes);

    std::transform(polygonsBeginIt, polygonsEndIt, vertexInsertIt, ganiullin::getNumOfVertexes);

    auto vertexBeginIt = std::begin(numVertexes);
    auto vertexEndIt = std::end(numVertexes);

    return (*std::min_element(vertexBeginIt, vertexEndIt));
  }
  size_t processCountEven(const PolyVector& polygons)
  {
    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);

    return std::count_if(polygonsBeginIt, polygonsEndIt, hasEvenVertexes);
  }
  size_t processCountOdd(const PolyVector& polygons)
  {
    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);

    return std::count_if(polygonsBeginIt, polygonsEndIt, hasOddVertexes);
  }
  size_t processCountVertexNum(const PolyVector& polygons, size_t vertexNum)
  {
    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto hasVertexesEqualToNum = std::bind(hasVertexesEqualTo, _1, vertexNum);

    return std::count_if(polygonsBeginIt, polygonsEndIt, hasVertexesEqualToNum);
  }
  bool processInFrame(const PolyVector& polygons, const ganiullin::Polygon& fig)
  {
    return ganiullin::isInFrame(fig, getFrame(polygons));
  }

  size_t processSame(const PolyVector& polygons, const ganiullin::Polygon& fig)
  {
    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto isSameAsFig = std::bind(ganiullin::isSame, _1, fig);

    return std::count_if(polygonsBeginIt, polygonsEndIt, isSameAsFig);
  }

  OutS& printAreaEven(const PolyVector& polygons, OutS& out)
  {
    ganiullin::iofmtguard iofmtguard(out);
    return out << std::fixed << std::setprecision(1) << processAreaEven(polygons);
  }
  OutS& printAreaOdd(const PolyVector& polygons, OutS& out)
  {
    ganiullin::iofmtguard iofmtguard(out);
    return out << std::fixed << std::setprecision(1) << processAreaOdd(polygons);
  }
  OutS& printAreaMean(const PolyVector& polygons, OutS& out)
  {
    ganiullin::iofmtguard iofmtguard(out);
    return out << std::fixed << std::setprecision(1) << processAreaMean(polygons);
  }
  OutS& printMaxArea(const PolyVector& polygons, OutS& out)
  {
    ganiullin::iofmtguard iofmtguard(out);
    return out << std::fixed << std::setprecision(1) << processMaxArea(polygons);
  }
  OutS& printMinArea(const PolyVector& polygons, OutS& out)
  {
    ganiullin::iofmtguard iofmtguard(out);
    return out << std::fixed << std::setprecision(1) << processMinArea(polygons);
  }

  OutS& printMaxVertexNum(const PolyVector& polygons, OutS& out)
  {
    return out << processMaxVertexNum(polygons);
  }
  OutS& printMinVertexNum(const PolyVector& polygons, OutS& out)
  {
    ganiullin::iofmtguard iofmtguard(out);
    return out << std::fixed << std::setprecision(1) << processMinVertexNum(polygons);
  }
  OutS& printCountEven(const PolyVector& polygons, OutS& out)
  {
    return out << processCountEven(polygons);
  }
  OutS& printCountOdd(const PolyVector& polygons, OutS& out)
  {
    return out << processCountOdd(polygons);
  }

  OutS& printAreaVertexNum(const PolyVector& polygons, size_t vertexNum, OutS& out)
  {
    ganiullin::iofmtguard iofmtguard(out);
    if (vertexNum < 3) {
      throw std::logic_error("Polygon should have more vertexes");
    }
    return out << std::fixed << std::setprecision(1) << processAreaVertexNum(polygons, vertexNum);
  }
  OutS& printCountVertexNum(const PolyVector& polygons, size_t vertexNum, OutS& out)
  {
    if (vertexNum < 3) {
      throw std::logic_error("Polygon should have more vertexes");
    }
    return out << processCountVertexNum(polygons, vertexNum);
  }

  OutS& printInFrame(const PolyVector& polygons, const ganiullin::Polygon& fig, OutS& out)
  {
    ganiullin::printBool(out, processInFrame(polygons, fig));
    return out;
  }

  OutS& printSame(const PolyVector& polygons, const ganiullin::Polygon& fig, OutS& out)
  {
    return out << processSame(polygons, fig);
  }
}

OutS& ganiullin::printErrorMessage(OutS& out)
{
  return out << "<INVALID COMMAND>";
}
OutS& ganiullin::printBool(OutS& out, bool val)
{
  if (val) {
    out << "<TRUE>";
  } else {
    out << "<FALSE>";
  }
  return out;
}

ganiullin::CommandHandler::CommandHandler():
  polygonCommandDict_(),
  vertexCommandDict_(),
  stateCommandDict_()
{
  stateCommandDict_.insert({"AREA EVEN", printAreaEven});
  stateCommandDict_.insert({"AREA ODD", printAreaOdd});
  stateCommandDict_.insert({"AREA MEAN", printAreaMean});
  stateCommandDict_.insert({"MIN AREA", printMinArea});
  stateCommandDict_.insert({"MIN VERTEXES", printMinVertexNum});
  stateCommandDict_.insert({"MAX AREA", printMaxArea});
  stateCommandDict_.insert({"MAX VERTEXES", printMaxVertexNum});
  stateCommandDict_.insert({"COUNT EVEN", printCountEven});
  stateCommandDict_.insert({"COUNT ODD", printCountOdd});

  vertexCommandDict_.insert({"AREA", printAreaVertexNum});
  vertexCommandDict_.insert({"COUNT", printCountVertexNum});

  polygonCommandDict_.insert({"INFRAME", printInFrame});
  polygonCommandDict_.insert({"SAME", printSame});
}
using CommHand = ganiullin::CommandHandler;
std::string CommHand::readCommand(InS& in) const
{
  std::string command;
  in >> command;
  if (!in) {
    throw std::runtime_error("Failed to read command");
  }
  if (polygonCommandDict_.find(command) == std::end(polygonCommandDict_)) {
    std::string param;
    in >> param;
    if (!in) {
      throw std::invalid_argument("Invalid command parameter");
    }
    command = command + " " + param;
  }
  return command;
}
OutS& CommHand::execCommand(const std::string& command, const PolyVector& polygons, InS& in, OutS& out) const
{
  if (stateCommandDict_.find(command) != std::end(stateCommandDict_)) {
    (*stateCommandDict_.find(command)).second(polygons, out);
    return out;
  }
  if (polygonCommandDict_.find(command) != std::end(polygonCommandDict_)) {
    Polygon param;
    in >> param >> DelimiterIO{'\n'};

    if (!in) {
      in.setstate(std::ios::failbit);
      return out;
    }
    (*polygonCommandDict_.find(command)).second(polygons, param, out);
    return out;
  }
  size_t pos = command.find(' ');
  std::string commandText = command.substr(0, pos);
  if (vertexCommandDict_.find(commandText) != std::end(vertexCommandDict_)) {
    size_t num = stoull(command.substr(pos));
    (*vertexCommandDict_.find(commandText)).second(polygons, num, out);
    return out;
  }
  if (!in.eof()) {
    in.setstate(std::ios::failbit);
    return out;
  }
  return out;
}
