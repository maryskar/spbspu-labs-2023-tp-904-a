#include "commands.h"
#include <ostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <functional>
#include <list>
#include "polygon.h"
#include "stream_guard.h"

using namespace std::placeholders;

namespace kumachev {
  static bool isEven(const Polygon &p)
  {
    return getVerticesCount(p) % 2 == 0;
  }

  static bool isOdd(const Polygon &p)
  {
    return !isEven(p);
  }

  static double intoEvenArea(const Polygon &p)
  {
    return isEven(p) ? getArea(p) : 0.0;
  }

  static double intoOddArea(const Polygon &p)
  {
    return isOdd(p) ? getArea(p) : 0.0;
  }

  static double intoVertexArea(const Polygon &p, size_t vertexCount)
  {
    return (getVerticesCount(p) == vertexCount) ? getArea(p) : 0.0;
  }

  void areaEven(const std::vector< Polygon > &polygons, std::ostream &ostream)
  {
    std::vector< double > areas;
    areas.reserve(polygons.size());
    auto inserter = std::back_inserter(areas);
    std::transform(polygons.begin(), polygons.end(), inserter, intoEvenArea);
    double area = std::accumulate(areas.begin(), areas.end(), 0.0);

    StreamGuard guard(ostream);
    ostream << std::fixed << std::setprecision(1) << area;
  }

  void areaOdd(const std::vector< Polygon > &polygons, std::ostream &ostream)
  {
    std::vector< double > areas;
    areas.reserve(polygons.size());
    auto inserter = std::back_inserter(areas);
    std::transform(polygons.begin(), polygons.end(), inserter, intoOddArea);
    double area = std::accumulate(areas.begin(), areas.end(), 0.0);

    StreamGuard guard(ostream);
    ostream << std::fixed << std::setprecision(1) << area;
  }

  void areaMean(const std::vector< Polygon > &polygons, std::ostream &ostream)
  {
    if (polygons.empty()) {
      throw std::logic_error("Polygon list is empty");
    }

    std::vector< double > areas;
    areas.reserve(polygons.size());
    auto inserter = std::back_inserter(areas);
    std::transform(polygons.begin(), polygons.end(), inserter, getArea);
    double total = std::accumulate(areas.begin(), areas.end(), 0.0);
    double mean = total / static_cast<double>(polygons.size());

    StreamGuard guard(ostream);
    ostream << std::fixed << std::setprecision(1) << mean;
  }

  void areaVertex(const std::vector< Polygon > &polygons, size_t vertex,
      std::ostream &ostream)
  {
    auto transformer = std::bind(intoVertexArea, _1, vertex);
    std::vector< double > areas;
    areas.reserve(polygons.size());
    auto inserter = std::back_inserter(areas);
    std::transform(polygons.begin(), polygons.end(), inserter, transformer);
    double area = std::accumulate(areas.begin(), areas.end(), 0.0);

    StreamGuard guard(ostream);
    ostream << std::fixed << std::setprecision(1) << area;
  }

  void maxArea(const std::vector< Polygon > &polygons, std::ostream &ostream)
  {
    if (polygons.empty()) {
      throw std::logic_error("Polygon list is empty");
    }

    std::vector< double > areas;
    areas.reserve(polygons.size());
    auto inserter = std::back_inserter(areas);
    std::transform(polygons.begin(), polygons.end(), inserter, getArea);
    auto max = std::max_element(areas.begin(), areas.end());

    StreamGuard guard(ostream);
    ostream << std::fixed << std::setprecision(1) << *max;
  }

  void minArea(const std::vector< Polygon > &polygons, std::ostream &ostream)
  {
    if (polygons.empty()) {
      throw std::logic_error("Polygon list is empty");
    }

    std::vector< double > areas;
    areas.reserve(polygons.size());
    auto inserter = std::back_inserter(areas);
    std::transform(polygons.begin(), polygons.end(), inserter, getArea);
    auto min = std::min_element(areas.begin(), areas.end());

    StreamGuard guard(ostream);
    ostream << std::fixed << std::setprecision(1) << *min;
  }

  void maxVert(const std::vector< Polygon > &polygons, std::ostream &ostream)
  {
    if (polygons.empty()) {
      throw std::logic_error("Polygon list is empty");
    }

    std::vector< size_t > vertexCount;
    vertexCount.reserve(polygons.size());
    auto inserter = std::back_inserter(vertexCount);
    auto begin = polygons.begin();
    auto end = polygons.end();
    std::transform(begin, end, inserter, getVerticesCount);

    auto max = std::max_element(vertexCount.begin(), vertexCount.end());
    StreamGuard guard(ostream);
    ostream << std::fixed << *max;
  }

  void minVert(const std::vector< Polygon > &polygons, std::ostream &ostream)
  {
    if (polygons.empty()) {
      throw std::logic_error("Polygon list is empty");
    }

    std::vector< size_t > vertexCount;
    vertexCount.reserve(polygons.size());
    auto inserter = std::back_inserter(vertexCount);
    auto begin = polygons.begin();
    auto end = polygons.end();
    std::transform(begin, end, inserter, getVerticesCount);

    auto min = std::min_element(vertexCount.begin(), vertexCount.end());
    StreamGuard guard(ostream);
    ostream << std::fixed << *min;
  }

  void countEven(const std::vector< Polygon > &polygons, std::ostream &ostream)
  {
    size_t count = std::count_if(polygons.begin(), polygons.end(), isEven);
    StreamGuard guard(ostream);
    ostream << std::fixed << count;
  }

  void countOdd(const std::vector< Polygon > &polygons, std::ostream &ostream)
  {
    size_t count = std::count_if(polygons.begin(), polygons.end(), isOdd);
    StreamGuard guard(ostream);
    ostream << std::fixed << count;
  }

  void countVert(const std::vector< Polygon > &polygons, size_t vert,
      std::ostream &ostream)
  {
    auto getVertCount = std::bind(getVerticesCount, _1);
    auto matchVert = std::bind(std::equal_to<>{}, getVertCount, vert);
    size_t count = std::count_if(polygons.begin(), polygons.end(), matchVert);
    StreamGuard guard(ostream);
    ostream << std::fixed << count;
  }

  void echo(std::vector< Polygon > &polygons, const Polygon &polygon,
      std::ostream &ostream)
  {
    std::list< Polygon > polygonList(polygons.begin(), polygons.end());
    auto equal = std::bind(std::equal_to<>{}, _1, polygon);
    auto search = std::find_if(polygonList.begin(), polygonList.end(), equal);
    size_t echoed = 0;

    while (search != polygonList.end()) {
      ++echoed;
      polygonList.insert(search, polygon);
      ++search;
      search = std::find_if(search, polygonList.end(), equal);
    }

    polygons.assign(polygonList.begin(), polygonList.end());
    StreamGuard guard(ostream);
    ostream << std::fixed << echoed;
  }

  void rmEcho(std::vector< Polygon > &polygons, const Polygon &polygon,
      std::ostream &ostream)
  {
    auto firstEqual = std::bind(std::equal_to<>{}, _1, polygon);
    auto secondEqual = std::bind(std::equal_to<>{}, _2, polygon);
    auto equal = std::bind(std::logical_and<>{}, firstEqual, secondEqual);
    std::list< Polygon > pList(polygons.begin(), polygons.end());

    auto search = std::adjacent_find(pList.begin(), pList.end(), equal);
    size_t removed = 0;

    while (search != pList.end()) {
      ++removed;
      search = pList.erase(search);
      search = std::adjacent_find(search, pList.end(), equal);
    }

    polygons.assign(pList.begin(), pList.end());
    StreamGuard guard(ostream);
    ostream << std::fixed << removed;
  }
}
