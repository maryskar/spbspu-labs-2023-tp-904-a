#ifndef COMMANDS_H
#define COMMANDS_H

#include <algorithm>
#include <iomanip>
#include "dataStructs.h"
#include "commandsImpl.h"
#include "workWithIO.h"
#include "commandsMapsAliases.h"

namespace potapova
{
  template< ParityFlags ParityFlag >
  void printSumOfSpecificAreas(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out)
  {
    double sum = 0.0;
    sum = getSumOfSpecificAreas< ParityFlag >(polygons);
    out << std::fixed << std::setprecision(1) << sum << '\n';
  }

  void printAverageArea(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out);

  void printSumOfAreasWithSpecificPointsNum(const std::deque< Polygon >& polygons,
      size_t target_count_points,
      std::istream& in,
      std::ostream& out);

  template< GetExtremeElemFunc GetExtremeElem >
  void printExtremeArea(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("There are no polygons");
    }
    double res = getArea(*GetExtremeElem(polygons.begin(), polygons.end(), comparePolygonsAreas));
    out << std::fixed << std::setprecision(1) << res << '\n';
  }

  template< GetExtremeElemFunc GetExtremeElem >
  void printExtremePoints(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("There are no polygons");
    }
    out << GetExtremeElem(polygons.begin(), polygons.end(), comparePolygonsPoints)->points.size() << '\n';
  }

  template< ParityFlags ParityFlag >
  void printPolygonsCountWithSpecificPointsNum(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out) noexcept
  {
    out << std::count_if(polygons.begin(), polygons.end(), isSpecificPointsNum< ParityFlag >) << '\n';
  }

  void printPolygonsNumWithTargetPointsNum(const std::deque< Polygon >& polygons,
      size_t target_count_points,
      std::istream& in,
      std::ostream& out);

  void removePolygonDuplicates(std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out);

  void printIsPolygonInFrame(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out);
}

#endif
