#include "commandsImpl.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <functional>
#include <stdexcept>
#include "rectangle.h"

namespace potapova
{
  using namespace std::placeholders;

  void getAverageArea(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream& err)
  {
    if (polygons.empty())
    {
      err << "<INVALID COMMAND>\n";
    }
    double sum_of_areas = 0.0;
    try
    {
      sum_of_areas = getSumOfAreas(polygons);
    }
    catch (const std::logic_error&)
    {
      err << "<INVALID COMMAND>\n";
    }
    double average_area = sum_of_areas / static_cast< double >(polygons.size());
    out << average_area << '\n';
  }

  void printSumOfAreasWithSpecificPointsCounts(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream& err)
  {
    size_t num_points = 0;
    in >> num_points;
    double sum_areas;
    try
    {
      sum_areas = std::accumulate(polygons.begin(),
        polygons.end(),
        0.0,
        std::bind(addAreaToSumIfNumPoints, _1, _2, num_points));
    }
    catch (const std::logic_error&)
    {
      err << "<INVALID COMMAND>\n";
    }
    out << sum_areas << '\n';
  }

  void countPolygonsWithOddPointsNum(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    out << std::count_if(polygons.begin(), polygons.end(), isOddPointNum) << '\n';
  }

  void countPolygonsWithEvenPointsNum(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    out << std::count_if(polygons.begin(), polygons.end(), isEvenPointNum) << '\n';
  }

  void countPolygonsWithPointsNum(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream&)
  {
    size_t num_points = 0;
    in >> num_points;
    out << std::count_if(polygons.begin(), polygons.end(), std::bind(checkDesiredNumPoints, num_points, _1)) << '\n';
  }

  void removePolygonDuplicates(std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream&)
  {
    Polygon target_polygon;
    in >> target_polygon;
    auto new_end_iter = std::unique(polygons.begin(),
      polygons.end(),
      std::bind(isEqual, _1, _2, target_polygon));
    ptrdiff_t count_removed = std::distance(new_end_iter, polygons.end());
    polygons.erase(new_end_iter, polygons.end());
    out << count_removed << '\n';
  }

  void checkPolygonInFrame(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream&)
  {
    Rectangle frame;
    frame.expandBounds(polygons);
    Polygon input_polygon;
    in >> input_polygon;
    if (frame.isPolygonInFrame(input_polygon))
    {
      out << "TRUE\n";
    }
    else
    {
      out << "FALSE\n";
    }
  }
}
