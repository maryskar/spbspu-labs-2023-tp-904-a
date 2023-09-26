#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <iomanip>
#include <vector>
#include <limits>
#include "polygon.hpp"

namespace gulyaev
{
  bool isEven(const Polygon &pol)
  {
    return (getSize(pol) % 2 == 0);
  }
  bool isOdd(const Polygon &pol)
  {
    return (getSize(pol) % 2 == 1);
  }
  bool numOfVertices(const Polygon &pol, std::size_t num)
  {
    return (getSize(pol) == num);
  }
  double getAreaIf(const Polygon &pol, std::function< bool (Polygon) > predicate)
  {
    if (predicate(pol)) {
      return getArea(pol);
    }
    return 0.0;
  }
  int countNum(std::string &s)
  {
    int num = 0;
    std::size_t pos;
    num = std::stoi(s, &pos);
    return (pos == s.size() ? num : 0);
  }

  double getAreasIf(const std::vector< Polygon > &data, std::function< double (Polygon) > predicate)
  {
    using namespace std::placeholders;
    std::vector< double > areas;
    areas.reserve(data.size());
    std::transform(data.cbegin(), data.cend(), std::back_inserter(areas), predicate);
    double result = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
    return result;
  }
  template< class T >
  double getMax(const std::vector< Polygon > &data, std::function< T (Polygon) > func)
  {
    std::vector< double > areas;
    areas.reserve(data.size());
    std::transform(std::cbegin(data), std::cend(data), std::back_inserter(areas), func);
    return *(std::max_element(std::cbegin(areas), std::cend(areas)));
  }
  template< class T >
  double getMin(const std::vector< Polygon > &data, std::function< T (Polygon) > func)
  {
    std::vector< double > areas;
    areas.reserve(data.size());
    std::transform(std::cbegin(data), std::cend(data), std::back_inserter(areas), func);
    return *(std::min_element(std::cbegin(areas), std::cend(areas)));
  }
  unsigned int getCountOfPolygonsIf(const std::vector< Polygon > &data, std::function< bool (Polygon) > pred)
  {
    unsigned int count = std::count_if(std::cbegin(data), std::cend(data), pred);
    return count;
  }

  void printArea(const std::vector< Polygon > &data, std::istream &in, std::ostream &out)
  {
    std::string cmd;
    std::getline(in, cmd, '\n');
    out << std::fixed << std::setprecision(1);
    using namespace std::placeholders;
    if (cmd == " EVEN") {
      out << getAreasIf(data, std::bind(getAreaIf, _1, isEven)) << "\n";
    } else if (cmd == " ODD") {
      out << getAreasIf(data, std::bind(getAreaIf, _1, isOdd)) << "\n";
    } else if (cmd == " MEAN") {
      if (data.empty()) {
      throw std::invalid_argument("<INVALID COMMAND>");
      }
      out << getAreasIf(data, std::bind(getArea, _1)) / data.size() << "\n";
    } else {
      try {
        int num = countNum(cmd);
        if (num > 2) {
          std::function< bool (Polygon) > predict = std::bind(numOfVertices, _1, num);
          out << getAreasIf(data, std::bind(getAreaIf, _1, predict)) << "\n";
        } else {
          throw std::invalid_argument("<INVALID COMMAND>");
        }
      } catch (const std::invalid_argument &e) {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
    }
  }
  void printMax(const std::vector< Polygon > &data, std::istream &in, std::ostream &out)
  {
    std::string cmd;
    std::getline(in, cmd, '\n');
    if (data.empty()) {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    if (cmd == " AREA") {
      out << std::fixed << std::setprecision(1) << getMax< double >(data, getArea) << "\n";
    } else if (cmd == " VERTEXES") {
      out << getMax< std::size_t >(data, getSize) << "\n";
    } else {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  void printMin(const std::vector< Polygon > &data, std::istream &in, std::ostream &out)
  {
    std::string cmd;
    std::getline(in, cmd, '\n');
    if (data.empty()) {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    if (cmd == " AREA") {
      out << std::fixed << std::setprecision(1) << getMin< double >(data, getArea) << "\n";
    } else if (cmd == " VERTEXES") {
      out << getMin< std::size_t >(data, getSize) << "\n";
    } else {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  void printCount(const std::vector< Polygon > &data, std::istream &in, std::ostream &out)
  {
    std::string cmd;
    std::getline(in, cmd, '\n');
    if (cmd == " EVEN") {
      out << getCountOfPolygonsIf(data, isEven) << "\n";
    } else if (cmd == " ODD") {
      out << getCountOfPolygonsIf(data, isOdd) << "\n";
    } else {
      try {
        int num = countNum(cmd);
        if (num > 2) {
          using namespace std::placeholders;
          out << getCountOfPolygonsIf(data, std::bind(numOfVertices, _1, num)) << "\n";
        } else {
          throw std::invalid_argument("<INVALID COMMAND>");
        }
      } catch (const std::invalid_argument &e) {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
    }
  }
  void printPerms(const std::vector< Polygon > &data, std::istream &in, std::ostream &out)
  {
    Polygon polygon;
    in >> polygon;
    if (in) {
      using namespace std::placeholders;
      out << getCountOfPolygonsIf(data, std::bind(checkPermutation, _1, polygon)) << "\n";
    } else {
      throw std::ios::failure("<INVALID COMMAND>");
    }
  }
  void printRightShapes(const std::vector< Polygon > &data, std::istream &in, std::ostream &out)
  {
    std::string cmd;
    std::getline(in, cmd, '\n');
    if (!cmd.empty()) {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    out << getCountOfPolygonsIf(data, checkRightShape) << "\n";
  }
}
