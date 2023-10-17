#ifndef COMMANDS_H
#define COMMANDS_H

#include <deque>
#include "dataStruct.h"
#include "funcForCommands.h"

namespace potapova
{
  void getSumAreasPolygonsOdd(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&);

  void getSumAreasPolygonsEven(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&);

  void getAverageArea(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&);

  void getSumOfAreasWithPointCounts(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream&);

  using PoligonsConstIterator = std::deque< Polygon >::const_iterator;
  using ComparePolygonsFunc = bool(*)(const Polygon&, const Polygon&);

  template< PoligonsConstIterator(*GetExtremeElem)(PoligonsConstIterator, PoligonsConstIterator, ComparePolygonsFunc) >
  void printExtremeArea(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    if (polygons.empty())
    {
      throw std::logic_error("Invalid number of polygons");
    }
    out << getArea(*GetExtremeElem(polygons.begin(), polygons.end(), comparePolygonsAreas)) << '\n';
  }

  template< PoligonsConstIterator(*GetExtremeElem)(PoligonsConstIterator, PoligonsConstIterator, ComparePolygonsFunc) >
  void printExtremePoints(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    if (polygons.empty())
    {
      throw std::logic_error("Invalid number of polygons");
    }
    out << GetExtremeElem(polygons.begin(), polygons.end(), comparePolygonsPoints)->points.size() << '\n';
  }

  void countPolygonsWithOddPointsNum(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&);

  void countPolygonsWithEvenPointsNum(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&);

  void countPolygonsWithPointsNum(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream&);

  void removePolygonDuplicates(std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream&);

  void checkPolygonInFrame(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream&);
}

#endif
