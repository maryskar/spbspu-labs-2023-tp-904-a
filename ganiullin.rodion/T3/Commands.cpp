#include "Commands.h"

#include <algorithm>
#include <functional>
#include <iomanip>
#include <numeric>
#include <stdexcept>
#include "FormatGuard.h"
#include "TypesIO.h"

namespace {
  using namespace std::placeholders;

  const auto getNumOfVertexes = std::bind(ganiullin::getNumOfVertexes, _1);
  const auto hasEvenVertexes = std::bind(std::equal_to< size_t >{},
      std::bind(std::modulus< size_t >{}, getNumOfVertexes, 2), 0);
  const auto hasOddVertexes =
      std::bind(std::logical_not< bool >{}, hasEvenVertexes);
  const auto hasVertexesEqualTo =
      std::bind(std::equal_to< size_t >{}, getNumOfVertexes, _2);

  double processAreaEven(const std::vector< ganiullin::Polygon >& polygons)
  {
    std::vector< ganiullin::Polygon > filteredPolygons;
    std::vector< double > areas;

    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto filteredInsertIt = std::back_inserter(filteredPolygons);

    std::copy_if(polygonsBeginIt, polygonsEndIt, filteredInsertIt,
        hasEvenVertexes);
    areas.reserve(filteredPolygons.size());

    auto filterBeginIt = std::begin(filteredPolygons);
    auto filterEndIt = std::end(filteredPolygons);
    auto areasInsertIt = std::back_inserter(areas);

    std::transform(filterBeginIt, filterEndIt, areasInsertIt,
        ganiullin::getArea);

    return std::accumulate(std::begin(areas), std::end(areas), 0.0);
  }
  double processAreaOdd(const std::vector< ganiullin::Polygon >& polygons)
  {
    std::vector< ganiullin::Polygon > filteredPolygons;
    std::vector< double > areas;

    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto filteredInsertIt = std::back_inserter(filteredPolygons);

    std::copy_if(polygonsBeginIt, polygonsEndIt, filteredInsertIt,
        hasOddVertexes);
    areas.reserve(filteredPolygons.size());

    auto filterBeginIt = std::begin(filteredPolygons);
    auto filterEndIt = std::end(filteredPolygons);
    auto areasInsertIt = std::back_inserter(areas);

    std::transform(filterBeginIt, filterEndIt, areasInsertIt,
        ganiullin::getArea);
    auto areasBeginIt = std::begin(areas);
    auto areasEndIt = std::end(areas);

    return std::accumulate(areasBeginIt, areasEndIt, 0.0);
  }
  double processAreaMean(const std::vector< ganiullin::Polygon >& polygons)
  {
    if (polygons.size() == 0) {
      throw std::logic_error("Polygons vector should not be empty");
    }
    std::vector< double > areas;
    areas.reserve(polygons.size());

    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto areasInsertIt = std::back_inserter(areas);

    std::transform(polygonsBeginIt, polygonsEndIt, areasInsertIt,
        ganiullin::getArea);
    auto areasBeginIt = std::begin(areas);
    auto areasEndIt = std::end(areas);

    return std::accumulate(areasBeginIt, areasEndIt, 0.0) / polygons.size();
  }
  double processAreaVertexNum(const std::vector< ganiullin::Polygon >& polygons,
      size_t vertexNum)
  {
    std::vector< ganiullin::Polygon > filteredPolygons;
    std::vector< double > areas;

    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto filteredInsertIt = std::back_inserter(filteredPolygons);

    std::copy_if(polygonsBeginIt, polygonsEndIt, filteredInsertIt,
        std::bind(hasVertexesEqualTo, _1, vertexNum));
    areas.reserve(filteredPolygons.size());

    auto filterBeginIt = std::begin(filteredPolygons);
    auto filterEndIt = std::end(filteredPolygons);
    auto areasInsertIt = std::back_inserter(areas);

    std::transform(filterBeginIt, filterEndIt, areasInsertIt,
        ganiullin::getArea);

    auto areasBeginIt = std::begin(areas);
    auto areasEndIt = std::end(areas);

    return std::accumulate(areasBeginIt, areasEndIt, 0.0);
  }

  double processMaxArea(const std::vector< ganiullin::Polygon >& polygons)
  {
    if (polygons.size() == 0) {
      throw std::logic_error("Polygons vector should not be empty");
    }
    std::vector< double > areas;
    areas.reserve(polygons.size());

    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto areasInsertIt = std::back_inserter(areas);

    std::transform(polygonsBeginIt, polygonsEndIt, areasInsertIt,
        ganiullin::getArea);

    auto areasBeginIt = std::begin(areas);
    auto areasEndIt = std::end(areas);

    return (*std::max_element(areasBeginIt, areasEndIt));
  }
  size_t processMaxVertexNum(const std::vector< ganiullin::Polygon >& polygons)
  {
    if (polygons.size() == 0) {
      throw std::logic_error("Polygons vector should not be empty");
    }
    std::vector< size_t > numVertexes;
    numVertexes.reserve(polygons.size());

    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto vertexInsertIt = std::back_inserter(numVertexes);

    std::transform(polygonsBeginIt, polygonsEndIt, vertexInsertIt,
        ganiullin::getNumOfVertexes);

    auto vertexBeginIt = std::begin(numVertexes);
    auto vertexEndIt = std::end(numVertexes);

    return (*std::max_element(vertexBeginIt, vertexEndIt));
  }

  double processMinArea(const std::vector< ganiullin::Polygon >& polygons)
  {
    if (polygons.size() == 0) {
      throw std::logic_error("Polygons vector should not be empty");
    }
    std::vector< double > areas;
    areas.reserve(polygons.size());

    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto areasInsertIt = std::back_inserter(areas);

    std::transform(polygonsBeginIt, polygonsEndIt, areasInsertIt,
        ganiullin::getArea);

    auto areasBeginIt = std::begin(areas);
    auto areasEndIt = std::end(areas);

    return (*std::min_element(areasBeginIt, areasEndIt));
  }
  size_t processMinVertexNum(const std::vector< ganiullin::Polygon >& polygons)
  {
    if (polygons.size() == 0) {
      throw std::logic_error("Polygons vector should not be empty");
    }
    std::vector< size_t > numVertexes;
    numVertexes.reserve(polygons.size());

    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto vertexInsertIt = std::back_inserter(numVertexes);

    std::transform(polygonsBeginIt, polygonsEndIt, vertexInsertIt,
        ganiullin::getNumOfVertexes);

    auto vertexBeginIt = std::begin(numVertexes);
    auto vertexEndIt = std::end(numVertexes);

    return (*std::min_element(vertexBeginIt, vertexEndIt));
  }
  size_t processCountEven(const std::vector< ganiullin::Polygon >& polygons)
  {
    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);

    return std::count_if(polygonsBeginIt, polygonsEndIt, hasEvenVertexes);
  }
  size_t processCountOdd(const std::vector< ganiullin::Polygon >& polygons)
  {
    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);

    return std::count_if(polygonsBeginIt, polygonsEndIt, hasOddVertexes);
  }
  size_t processCountVertexNum(
      const std::vector< ganiullin::Polygon >& polygons, size_t vertexNum)
  {
    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto hasVertexesEqualToNum = std::bind(hasVertexesEqualTo, _1, vertexNum);

    return std::count_if(polygonsBeginIt, polygonsEndIt, hasVertexesEqualToNum);
  }
  std::string processInFrame(const std::vector< ganiullin::Polygon >& polygons,
      const ganiullin::Polygon& fig)
  {
    if (ganiullin::isInFrame(fig, getFrame(polygons))) {
      return "<TRUE>";
    }
    return "<FALSE>";
  }

  size_t processSame(const std::vector< ganiullin::Polygon >& polygons,
      const ganiullin::Polygon& fig)
  {
    auto polygonsBeginIt = std::begin(polygons);
    auto polygonsEndIt = std::end(polygons);
    auto isSameAsFig = std::bind(ganiullin::isSame, _1, fig);

    return std::count_if(polygonsBeginIt, polygonsEndIt, isSameAsFig);
  }

  std::ostream& printAreaEven(const std::vector< ganiullin::Polygon >& polygons,
      std::ostream& out)
  {
    ganiullin::iofmtguard iofmtguard(out);
    return out << std::fixed << std::setprecision(1)
               << processAreaEven(polygons);
  }
  std::ostream& printAreaOdd(const std::vector< ganiullin::Polygon >& polygons,
      std::ostream& out)
  {
    ganiullin::iofmtguard iofmtguard(out);
    return out << std::fixed << std::setprecision(1)
               << processAreaOdd(polygons);
  }
  std::ostream& printAreaMean(const std::vector< ganiullin::Polygon >& polygons,
      std::ostream& out)
  {
    ganiullin::iofmtguard iofmtguard(out);
    return out << std::fixed << std::setprecision(1)
               << processAreaMean(polygons);
  }
  std::ostream& printMaxArea(const std::vector< ganiullin::Polygon >& polygons,
      std::ostream& out)
  {
    ganiullin::iofmtguard iofmtguard(out);
    return out << std::fixed << std::setprecision(1)
               << processMaxArea(polygons);
  }
  std::ostream& printMinArea(const std::vector< ganiullin::Polygon >& polygons,
      std::ostream& out)
  {
    ganiullin::iofmtguard iofmtguard(out);
    return out << std::fixed << std::setprecision(1)
               << processMinArea(polygons);
  }

  std::ostream& printMaxVertexNum(
      const std::vector< ganiullin::Polygon >& polygons, std::ostream& out)
  {
    return out << processMaxVertexNum(polygons);
  }
  std::ostream& printMinVertexNum(
      const std::vector< ganiullin::Polygon >& polygons, std::ostream& out)
  {
    ganiullin::iofmtguard iofmtguard(out);
    return out << std::fixed << std::setprecision(1)
               << processMinVertexNum(polygons);
  }
  std::ostream& printCountEven(
      const std::vector< ganiullin::Polygon >& polygons, std::ostream& out)
  {
    return out << processCountEven(polygons);
  }
  std::ostream& printCountOdd(const std::vector< ganiullin::Polygon >& polygons,
      std::ostream& out)
  {
    return out << processCountOdd(polygons);
  }

  std::ostream& printAreaVertexNum(
      const std::vector< ganiullin::Polygon >& polygons, size_t vertexNum,
      std::ostream& out)
  {
    ganiullin::iofmtguard iofmtguard(out);
    if (vertexNum < 3) {
      throw std::logic_error("Polygon should have more vertexes");
    }
    return out << std::fixed << std::setprecision(1)
               << processAreaVertexNum(polygons, vertexNum);
  }
  std::ostream& printCountVertexNum(
      const std::vector< ganiullin::Polygon >& polygons, size_t vertexNum,
      std::ostream& out)
  {
    if (vertexNum < 3) {
      throw std::logic_error("Polygon should have more vertexes");
    }
    return out << processCountVertexNum(polygons, vertexNum);
  }

  std::ostream& printInFrame(const std::vector< ganiullin::Polygon >& polygons,
      const ganiullin::Polygon& fig, std::ostream& out)
  {
    return out << processInFrame(polygons, fig);
  }

  std::ostream& printSame(const std::vector< ganiullin::Polygon >& polygons,
      const ganiullin::Polygon& fig, std::ostream& out)
  {
    return out << processSame(polygons, fig);
  }
}

std::ostream& ganiullin::printErrorMessage(std::ostream& out)
{
  return out << "<INVALID COMMAND>";
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
std::string ganiullin::CommandHandler::readCommand(std::istream& in) const
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
std::ostream& ganiullin::CommandHandler::executeCommand(
    const std::string& command, const std::vector< Polygon >& polygons,
    std::istream& in, std::ostream& out) const
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
