#include "commands.h"
#include <functional>
#include "rectangle.h"

using namespace std::placeholders;

void potapova::printAverageArea(const std::deque< Polygon >& polygons,
    std::istream& in,
    std::ostream& out)
{
  if (polygons.empty())
  {
    handleInvalidCommand(in, out);
  }
  double sum_of_areas = 0.0;
  try
  {
    sum_of_areas = getSumOfAreas(polygons);
  }
  catch (const std::logic_error&)
  {
    handleInvalidCommand(in, out);
    return;
  }
  double average_area = sum_of_areas / static_cast< double >(polygons.size());
  out << std::fixed << std::setprecision(1) << average_area << '\n';
}

void potapova::printSumOfAreasWithSpecificPointsCounts(const std::deque< Polygon >& polygons,
    size_t target_count_points,
    std::istream& in,
    std::ostream& out)
{
  if (target_count_points < 3)
  {
    handleInvalidCommand(in, out);
    return;
  }
  double sum_areas = 0.0;
  try
  {
    sum_areas = std::accumulate(polygons.begin(),
      polygons.end(),
      0.0,
      std::bind(addAreaToSumIfNumPoints, _1, _2, target_count_points));
  }
  catch (const std::logic_error&)
  {
    potapova::handleInvalidCommand(in, out);
    return;
  }
  out << std::fixed << std::setprecision(1) << sum_areas << '\n';
}

void potapova::printPolygonsCountWithTargetPointsNum(const std::deque< Polygon >& polygons,
    size_t target_count_points,
    std::istream& in,
    std::ostream& out) noexcept
{
  if (target_count_points < 3)
  {
    handleInvalidCommand(in, out);
    return;
  }
  out << std::count_if(polygons.begin(), polygons.end(), std::bind(checkDesiredNumPoints, target_count_points, _1)) << '\n';
}

void potapova::removePolygonDuplicates(std::deque< Polygon >& polygons,
    std::istream& in,
    std::ostream& out)
{
  Polygon target_polygon;
  if (!(in >> target_polygon))
  {
    in.clear(std::ios_base::goodbit);
    handleInvalidCommand(in, out);
    return;
  }
  std::deque< Polygon >::iterator new_end_iter = std::unique(polygons.begin(),
    polygons.end(),
    std::bind(isEqual, _1, _2, target_polygon));
  ptrdiff_t count_removed = std::distance(new_end_iter, polygons.end());
  polygons.resize(polygons.size() - static_cast< size_t >(count_removed));
  out << count_removed << '\n';
}

void potapova::printIsPolygonInFrame(const std::deque< Polygon >& polygons,
    std::istream& in,
    std::ostream& out) noexcept
{
  Rectangle frame;
  frame.expandBoundsToPolygons(polygons);
  Polygon input_polygon;
  if (!(in >> input_polygon))
  {
    in.clear(std::ios_base::goodbit);
    handleInvalidCommand(in, out);
    return;
  }
  if (frame.isPolygonInFrame(input_polygon))
  {
    out << "TRUE\n";
  }
  else
  {
    out << "FALSE\n";
  }
}
