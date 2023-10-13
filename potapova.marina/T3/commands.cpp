#include "commands.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <functional>
#include <stdexcept>
#include "rectangle.h"
#include "funcForCommands.h"

namespace potapova
{
  using namespace std::placeholders;

  constexpr size_t ODD = 1;
  constexpr size_t EVEN = 0;

  void getSumAreasPolygonsOdd(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    double sum = getSumPolygonsAreasT<ODD>(polygons);
    out << sum << '\n';
  }

  void getSumAreasPolygonsEven(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    double sum = getSumPolygonsAreasT<EVEN>(polygons);
    out << sum << '\n';
  }

  void getAverageArea(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    size_t num_polygons = countPolygons(polygons);
    if (num_polygons < 1)
    {
      throw std::runtime_error("Incorrect number of polygons");
    }
    double all_area = getSumPolygonsAreas(polygons);
    double average_area = all_area / num_polygons;
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

  void getMaxArea(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    if (polygons.empty())
    {
      throw std::logic_error("Invalid number of polygons");
    }
    auto max_polygon_iter = std::max_element(polygons.begin(), polygons.end(), comparePolygonsAreas);
    double max_area = getPolygonArea(*max_polygon_iter);
    out << max_area << '\n';
  }

  void getMaxPoints(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    if (polygons.empty())
    {
      throw std::logic_error("Invalid number of polygons");
    }
    auto max_polygon_iter = std::max_element(polygons.begin(), polygons.end(), comparePolygonsPoints);
    double max_points = max_polygon_iter->points.size();
    out << max_points << '\n';
  }

  void getMinArea(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    if (polygons.empty())
    {
      throw std::logic_error("Invalid number of polygons");
    }
    auto min_polygon_iter = std::min_element(polygons.begin(), polygons.end(), comparePolygonsAreas);
    double min_area = getPolygonArea(*min_polygon_iter);
    out << min_area << '\n';
  }

  void getMinPoints(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    if (polygons.empty())
    {
      throw std::logic_error("Invalid number of polygons");
    }
    auto min_polygon_iter = std::min_element(polygons.begin(), polygons.end(), comparePolygonsPoints);
    double min_points = min_polygon_iter->points.size();
    out << min_points << '\n';
  }

  void countPolygonsWithOddPointsNum(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    size_t num_polygons = std::count_if(polygons.begin(), polygons.end(), isOddPointNum);
    out << num_polygons << '\n';
  }

  void countPolygonsWithEvenPointsNum(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    size_t num_polygons = std::count_if(polygons.begin(), polygons.end(), isEvenPointNum);
    out << num_polygons << '\n';
  }

  void countPolygonsWithPointsNum(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream&)
  {
    size_t num_points = 0;
    in >> num_points;
    size_t num_polygons = std::count_if(polygons.begin(), polygons.end(), checkDesiredNumPoints);
    out << num_polygons << '\n';
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
      std::bind(comparePolygonsEqual, _1, _2, target_polygon));
    size_t count_removed = 0;
    count_removed = std::distance(new_end_iter, polygons.end());
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
    if (isInFrame(frame, input_polygon))
    {
      out << "TRUE\n";
    }
    else
    {
      out << "FALSE\n";
    }
  }
}
