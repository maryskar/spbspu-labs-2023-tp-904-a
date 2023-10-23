#ifndef COMMANDS_H
#define COMMANDS_H

#include <algorithm>
#include "dataStructs.h"
#include "commandsImpl.h"
#include "workWithIO.h"
#include "commandsMapsAliases.h"

namespace potapova
{
  template< size_t ParityFlag >
  void printSumOfSpecificAreas(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out)
  {
    double sum = 0.0;
    try
    {
      sum = getSumOfSpecificAreas< ParityFlag >(polygons);
    }
    catch (const std::logic_error&)
    {
      potapova::handleInvalidCommand(in, out);
    }
    out << sum << '\n';
  }

  void printAverageArea(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out);

  void printSumOfAreasWithSpecificPointsCounts(const std::deque< Polygon >& polygons,
      size_t target_count_points,
      std::istream& in,
      std::ostream& out);

  template< GetExtremeElemFunc GetExtremeElem >
  void printExtremeArea(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out)
  {
    if (polygons.empty())
    {
      potapova::handleInvalidCommand(in, out);
      return;
    }
    out << getArea(*GetExtremeElem(polygons.begin(), polygons.end(), comparePolygonsAreas)) << '\n';
  }

  template< GetExtremeElemFunc GetExtremeElem >
  void printExtremePoints(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out) noexcept
  {
    if (polygons.empty())
    {
      potapova::handleInvalidCommand(in, out);
      return;
    }
    out << GetExtremeElem(polygons.begin(), polygons.end(), comparePolygonsPoints)->points.size() << '\n';
  }

  template< size_t ParityFlag >
  void printPolygonsCountWithSpecificPointsNum(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out) noexcept
  {
    out << std::count_if(polygons.begin(), polygons.end(), isSpecificPointsNum< ParityFlag >) << '\n';
  }

  void printPolygonsCountWithTargetPointsNum(const std::deque< Polygon >& polygons,
      size_t target_count_points,
      std::istream& in,
      std::ostream& out) noexcept;

  void removePolygonDuplicates(std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out);

  void printIsPolygonInFrame(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out) noexcept;
}

#endif
