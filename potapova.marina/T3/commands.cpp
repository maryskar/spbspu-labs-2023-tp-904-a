#include "commands.h"
#include <functional>
#include "rectangle.h"

namespace potapova
{
  using namespace std::placeholders;

  void printAverageArea(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream&)
  {
    if (polygons.empty())
    {
      potapova::handleInvalidCommand(in, out);
    }
    double sum_of_areas = 0.0;
    try
    {
      sum_of_areas = getSumOfAreas(polygons);
    }
    catch (const std::logic_error&)
    {
      potapova::handleInvalidCommand(in, out);
    }
    double average_area = sum_of_areas / static_cast< double >(polygons.size());
    out << average_area << '\n';
  }

  void printSumOfAreasWithSpecificPointsCounts(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream&)
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
      potapova::handleInvalidCommand(in, out);
    }
    out << sum_areas << '\n';
  }

  void printPolygonsCountWithTargetPointsNum(const std::deque< Polygon >& polygons,
      size_t target_count_poins,
      std::ostream& out) noexcept
  {
    out << std::count_if(polygons.begin(), polygons.end(), std::bind(checkDesiredNumPoints, target_count_poins, _1)) << '\n';
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
    polygons.resize(polygons.size() - static_cast< size_t >(count_removed));
    out << count_removed << '\n';
  }

  void printIsPolygonInFrame(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream&) noexcept
  {
    Rectangle frame;
    frame.expandBoundsToPolygons(polygons);
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
