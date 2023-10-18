#ifndef COMMANDS_H
#define COMMANDS_H

#include <algorithm>
#include <deque>
#include "dataStructs.h"
#include "commandsImpl.h"
#include "workWithIO.h"

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

  using PoligonsConstIterator = std::deque< Polygon >::const_iterator;
  using ComparePolygonsFunc = bool(*)(const Polygon&, const Polygon&);

  template< PoligonsConstIterator(*GetExtremeElem)(PoligonsConstIterator, PoligonsConstIterator, ComparePolygonsFunc) >
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

  template< PoligonsConstIterator(*GetExtremeElem)(PoligonsConstIterator, PoligonsConstIterator, ComparePolygonsFunc) >
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
    out << std::count_if(polygons.begin(), polygons.end(), isSpecificPointsNum<ParityFlag>) << '\n';
  }

  void printPolygonsCountWithTargetPointsNum(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream&) noexcept;

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
