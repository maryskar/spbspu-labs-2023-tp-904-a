#include "commands.h"
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

  void getSumAreasPolygonsOdd(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    double sum = getSumOfSpecificAreas< ODD >(polygons);
    out << sum << '\n';
  }

  void getSumAreasPolygonsEven(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    double sum = getSumOfSpecificAreas< EVEN >(polygons);
    out << sum << '\n';
  }

  void getAverageArea(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    size_t num_polygons = polygons.size();
    if (num_polygons < 1)
    {
      throw std::runtime_error("Incorrect number of polygons");
    }
    double all_area = getSumOfAreas(polygons);
    double average_area = all_area / static_cast< double >(num_polygons);
    out << average_area << '\n';
  }

  void getSumOfAreasWithPointCounts(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream&)
  {
    size_t num_points = 0;
    in >> num_points;
    double sum_areas = std::accumulate(polygons.begin(),
      polygons.end(),
      0.0,
      std::bind(addAreaToSumIfNumPoints, _1, _2, num_points));
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
    Rectangle frame = Rectangle::getRectWichCanInclude(polygons);
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
