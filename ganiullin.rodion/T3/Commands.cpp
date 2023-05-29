#include "Commands.h"

#include <algorithm>
#include <functional>
#include <iomanip>
#include <numeric>
#include <stdexcept>
#include "FormatGuard.h"

double processAreaEven(const std::vector< ganiullin::Polygon >& polygons)
{
  using namespace std::placeholders;
  std::vector< ganiullin::Polygon > filteredPolygons;
  std::vector< double > areas;
  auto hasEvenVertexes = std::bind(std::equal_to< size_t >{},
      std::bind(std::modulus< size_t >{},
          std::bind(ganiullin::getNumOfVertexes, _1), 2),
      0);
  std::copy_if(std::begin(polygons), std::end(polygons),
      std::back_inserter(filteredPolygons), hasEvenVertexes);
  std::transform(std::begin(filteredPolygons), std::end(filteredPolygons),
      std::back_inserter(areas), ganiullin::getArea);
  return std::accumulate(std::begin(areas), std::end(areas), 0.0);
}
double processAreaOdd(const std::vector< ganiullin::Polygon >& polygons)
{
  using namespace std::placeholders;
  auto hasOddVertex = std::bind(std::equal_to< size_t >{},
      std::bind(std::modulus< size_t >{},
          std::bind(ganiullin::getNumOfVertexes, _1), 2),
      1);
  std::vector< ganiullin::Polygon > filteredPolygons;
  std::vector< double > areas;
  std::copy_if(std::begin(polygons), std::end(polygons),
      std::back_inserter(filteredPolygons), hasOddVertex);
  std::transform(std::begin(filteredPolygons), std::end(filteredPolygons),
      std::back_inserter(areas), ganiullin::getArea);
  return std::accumulate(std::begin(areas), std::end(areas), 0.0);
}
double processAreaMean(const std::vector< ganiullin::Polygon >& polygons)
{
  if (polygons.size() == 0) {
    throw std::logic_error("Polygons vector should not be empty");
  }
  std::vector< double > areas;
  std::transform(std::begin(polygons), std::end(polygons),
      std::back_inserter(areas), ganiullin::getArea);
  return std::accumulate(std::begin(areas), std::end(areas), 0.0) /
         polygons.size();
}
double processAreaVertexNum(const std::vector< ganiullin::Polygon >& polygons,
    size_t vertexNum)
{
  using namespace std::placeholders;
  std::vector< ganiullin::Polygon > filteredPolygons;
  std::vector< double > areas;
  std::copy_if(std::begin(polygons), std::end(polygons),
      std::back_inserter(filteredPolygons),
      std::bind(std::equal_to< size_t >{},
          std::bind(ganiullin::getNumOfVertexes, _1), vertexNum));
  std::transform(std::begin(filteredPolygons), std::end(filteredPolygons),
      std::back_inserter(areas), ganiullin::getArea);
  return std::accumulate(std::begin(areas), std::end(areas), 0.0);
}

double processMaxArea(const std::vector< ganiullin::Polygon >& polygons)
{
  if (polygons.size() == 0) {
    throw std::logic_error("Polygons vector should not be empty");
  }
  std::vector< double > areas;
  std::transform(std::begin(polygons), std::end(polygons),
      std::back_inserter(areas), ganiullin::getArea);
  return (*std::max_element(std::begin(areas), std::end(areas)));
}
size_t processMaxVertexNum(const std::vector< ganiullin::Polygon >& polygons)
{
  if (polygons.size() == 0) {
    throw std::logic_error("Polygons vector should not be empty");
  }
  std::vector< size_t > numVertexes;

  std::transform(std::begin(polygons), std::end(polygons),
      std::back_inserter(numVertexes), ganiullin::getNumOfVertexes);
  return (*std::max_element(std::begin(numVertexes), std::end(numVertexes)));
}

double processMinArea(const std::vector< ganiullin::Polygon >& polygons)
{
  if (polygons.size() == 0) {
    throw std::logic_error("Polygons vector should not be empty");
  }
  std::vector< double > areas;
  std::transform(std::begin(polygons), std::end(polygons),
      std::back_inserter(areas), ganiullin::getArea);
  return (*std::min_element(std::begin(areas), std::end(areas)));
}
size_t processMinVertexNum(const std::vector< ganiullin::Polygon >& polygons)
{
  if (polygons.size() == 0) {
    throw std::logic_error("Polygons vector should not be empty");
  }
  std::vector< size_t > numVertexes;

  std::transform(std::begin(polygons), std::end(polygons),
      std::back_inserter(numVertexes), ganiullin::getNumOfVertexes);
  return (*std::min_element(std::begin(numVertexes), std::end(numVertexes)));
}
size_t processCountEven(const std::vector< ganiullin::Polygon >& polygons)
{
  using namespace std::placeholders;
  auto hasEvenVertexes = std::bind(std::equal_to< size_t >{},
      std::bind(std::modulus< size_t >{},
          std::bind(ganiullin::getNumOfVertexes, _1), 2),
      0);
  return std::count_if(std::begin(polygons), std::end(polygons),
      hasEvenVertexes);
}
size_t processCountOdd(const std::vector< ganiullin::Polygon >& polygons)
{
  using namespace std::placeholders;
  auto hasOddVertexes = std::bind(std::equal_to< size_t >{},
      std::bind(std::modulus< size_t >{},
          std::bind(ganiullin::getNumOfVertexes, _1), 2),
      1);
  return std::count_if(std::begin(polygons), std::end(polygons),
      hasOddVertexes);
}
size_t processCountVertexNum(const std::vector< ganiullin::Polygon >& polygons,
    size_t vertexNum)
{
  using namespace std::placeholders;
  return std::count_if(std::begin(polygons), std::end(polygons),
      std::bind(std::equal_to< size_t >{},
          std::bind(ganiullin::getNumOfVertexes, _1), vertexNum));
}
bool processInFrame(const std::vector< ganiullin::Polygon >& polygons,
    const ganiullin::Polygon& fig)
{
  return ganiullin::isInFrame(fig, getFrame(polygons));
}

size_t processSame(const std::vector< ganiullin::Polygon >& polygons,
    const ganiullin::Polygon& fig)
{
  using namespace std::placeholders;
  return std::count_if(std::begin(polygons), std::end(polygons),
      std::bind(ganiullin::isSame, _1, fig));
}

void ganiullin::printAreaEven(const std::vector< Polygon >& polygons,
    std::ostream& out)
{
  iofmtguard iofmtguard(out);
  out << std::setprecision(1) << processAreaEven(polygons);
}
void ganiullin::printAreaOdd(const std::vector< Polygon >& polygons,
    std::ostream& out)
{
  iofmtguard iofmtguard(out);
  out << std::setprecision(1) << processAreaOdd(polygons);
}
void ganiullin::printAreaMean(const std::vector< Polygon >& polygons,
    std::ostream& out)
{
  iofmtguard iofmtguard(out);
  out << std::setprecision(1) << processAreaMean(polygons);
}
void ganiullin::printMaxArea(const std::vector< Polygon >& polygons,
    std::ostream& out)
{
  iofmtguard iofmtguard(out);
  out << std::setprecision(1) << processMaxArea(polygons);
}
void ganiullin::printMinArea(const std::vector< Polygon >& polygons,
    std::ostream& out)
{
  iofmtguard iofmtguard(out);
  out << std::setprecision(1) << processMinArea(polygons);
}

void ganiullin::printMaxVertexNum(const std::vector< Polygon >& polygons,
    std::ostream& out)
{
  out << processMaxVertexNum(polygons);
}
void ganiullin::printMinVertexNum(const std::vector< Polygon >& polygons,
    std::ostream& out)
{
  iofmtguard iofmtguard(out);
  out << std::setprecision(1) << processAreaMean(polygons);
}
void ganiullin::printCountEven(const std::vector< Polygon >& polygons,
    std::ostream& out)
{
  out << processCountEven(polygons);
}
void ganiullin::printCountOdd(const std::vector< Polygon >& polygons,
    std::ostream& out)
{
  out << processCountOdd(polygons);
}

void ganiullin::printAreaVertexNum(const std::vector< Polygon >& polygons,
    size_t vertexNum, std::ostream& out)
{
  out << processAreaVertexNum(polygons, vertexNum);
}
void ganiullin::printCountVertexNum(const std::vector< Polygon >& polygons,
    size_t vertexNum, std::ostream& out)
{
  out << processCountVertexNum(polygons, vertexNum);
}

void ganiullin::printInFrame(const std::vector< Polygon >& polygons,
    const Polygon& fig, std::ostream& out)
{
  iofmtguard iofmtguard(out);
  out << '<' << std::boolalpha << std::uppercase
      << processInFrame(polygons, fig) << '>';
}
void ganiullin::printSame(const std::vector< Polygon >& polygons,
    const Polygon& fig, std::ostream& out)
{
  out << processSame(polygons, fig);
}

std::string ganiullin::readCommand(std::istream& in,
    const command_dicts_t& commandDict)
{
  using namespace std::placeholders;
  std::string command;
  in >> command;
  if (!in) {
    throw std::logic_error("EOF");
  }
  if (commandDict.polygonCommandDict.find(command) ==
      std::end(commandDict.polygonCommandDict)) {
    std::string param;
    in >> param;
    if (!in) {
      throw std::invalid_argument("Invalid command parameter");
    }
    command = command + " " + param;
  }
  return command;
}
void ganiullin::executeCommand(const std::string& command,
    const std::vector< Polygon > polygons, command_dicts_t commandDicts,
    std::istream& in, std::ostream& out)
{
  const auto& stateCommands = commandDicts.stateCommandDict;
  const auto& polygonCommands = commandDicts.polygonCommandDict;
  const auto& vertexCommands = commandDicts.vertexCommandDict;

  if (stateCommands.find(command) != std::end(stateCommands)) {
    (*stateCommands.find(command)).second(polygons, out);
    return;
  }
  if (polygonCommands.find(command) != std::end(polygonCommands)) {
    Polygon param;

    in >> param;
    if (!in || in.peek() != '\n') {
      in.setstate(std::ios::failbit);
      return;
    }
    (*polygonCommands.find(command)).second(polygons, param, out);
    return;
  }
  size_t pos = command.find(' ');
  if (vertexCommands.find(command.substr(0, pos)) != std::end(vertexCommands)) {
    size_t num = stoull(command.substr(pos));
    (*vertexCommands.find(command.substr(0, pos))).second(polygons, num, out);
    return;
  }
  if (!in.eof()) {
    in.setstate(std::ios::failbit);
    return;
  }
}
void ganiullin::printErrorMessage(std::ostream& out)
{
  out << "<INVALID COMMAND>";
}
ganiullin::command_dicts_t ganiullin::createCommandDicts()
{
  command_dicts_t commandDicts{};
  auto& polygonCommands = commandDicts.polygonCommandDict;
  auto& stateCommands = commandDicts.stateCommandDict;
  auto& vertexCommands = commandDicts.vertexCommandDict;

  stateCommands.insert({"AREA EVEN", printAreaEven});
  stateCommands.insert({"AREA ODD", printAreaOdd});
  stateCommands.insert({"AREA MEAN", printAreaMean});
  stateCommands.insert({"MIN AREA", printMinArea});
  stateCommands.insert({"MIN VERTEXES", printMinVertexNum});
  stateCommands.insert({"MAX AREA", printMaxArea});
  stateCommands.insert({"MAX VERTEXES", printMaxVertexNum});
  stateCommands.insert({"COUNT EVEN", printCountEven});
  stateCommands.insert({"COUNT ODD", printCountOdd});

  vertexCommands.insert({"AREA", printAreaVertexNum});
  vertexCommands.insert({"COUNT", printCountVertexNum});

  polygonCommands.insert({"INFRAME", printInFrame});
  polygonCommands.insert({"SAME", printSame});

  return commandDicts;
}
