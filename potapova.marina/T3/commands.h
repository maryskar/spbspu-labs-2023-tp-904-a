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
      std::istream&,
      std::ostream& out,
      std::ostream& err)
  {
    double sum;
    try
    {
      sum = getSumOfSpecificAreas< EVEN >(polygons);
    }
    catch (const std::logic_error&)
    {
      err << "<INVALID COMMAND>\n";
    }
    out << sum << '\n';
  }

  void printAverageArea(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream& err);

  void printSumOfAreasWithSpecificPointsCounts(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream& err);

  template< GetExtremeElemFunc GetExtremeElem >
  void printExtremeArea(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream& err)
  {
    if (polygons.empty())
    {
      err << "<INVALID COMMAND>\n";
    }
    out << getArea(*GetExtremeElem(polygons.begin(), polygons.end(), comparePolygonsAreas)) << '\n';
  }

  template< GetExtremeElemFunc GetExtremeElem >
  void printExtremePoints(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream& err) noexcept
  {
    if (polygons.empty())
    {
      err << "<INVALID COMMAND>\n";
    }
    out << GetExtremeElem(polygons.begin(), polygons.end(), comparePolygonsPoints)->points.size() << '\n';
  }

  template< size_t ParityFlag >
  void printPolygonsCountWithSpecificPointsNum(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&) noexcept
  {
    out << std::count_if(polygons.begin(), polygons.end(), isSpecificPointsNum< ParityFlag >) << '\n';
  }

  void printPolygonsCountWithTargetPointsNum(const std::deque< Polygon >& polygons,
      size_t target_count_poins,
      std::ostream& out) noexcept;

  void removePolygonDuplicates(std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream&);

  void printIsPolygonInFrame(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream&) noexcept;
}

#endif
