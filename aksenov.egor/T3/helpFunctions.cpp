#include "helpFunctions.h"
#include <vector>
#include <cmath>
#include "polygon.h"
namespace aksenov
{
  std::vector< double > getArea(const std::vector<Polygon> &pol)
  {
    std::vector< double > areas;
    for (const Polygon &p: pol) {
      const std::vector< Point > &points = p.points;
      double firstSum = 0.0;
      double secondSum = 0.0;
      for (size_t i = 0; i < points.size(); i++) {
        const Point &current = points[i];
        const Point &next = points[(i + 1) % points.size()];
        firstSum += (static_cast< double >(next.y * current.x));
        secondSum += (static_cast< double >(next.x * current.y));
      }
      areas.push_back(std::fabs((firstSum - secondSum) / 2));
    }
    return areas;
  }

  bool isOdd(const Polygon& data)
  {
    return data.points.size() % 2;
  }

  bool isEven(const Polygon& data)
  {
    return !(isOdd(data));
  }

  bool isInteger(const std::string & s)
  {
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
    char * p = nullptr;
    strtol(s.c_str(), &p, 10);
    return (*p == 0);
  }

  bool isNotEqual(const Polygon &pol, size_t num)
  {
    return pol.points.size() != num;
  }

  bool isEqual(const Polygon &pol, size_t amount)
  {
    return pol.points.size() == amount;
  }

  bool comparePoints(const Point &lhs, const Point &rhs)
  {
    if (lhs.x == rhs.x) {
      return lhs.y < rhs.y;
    }
    return lhs.x < rhs.x;
  }

  Point translatePoint(const Point& point, int diffX, int diffY)
  {
    Point translatedPoint;
    translatedPoint.x = point.x + diffX;
    translatedPoint.y = point.y + diffY;
    return translatedPoint;
  }

  bool isSame(const Polygon& lhs, const Polygon& rhs)
  {
    if (lhs.points.size() != rhs.points.size()) {
      return false;
    }

    std::vector<Point> lhsSorted(lhs.points);
    std::vector<Point> rhsSorted(rhs.points);

    std::sort(lhsSorted.begin(), lhsSorted.end(), comparePoints);
    std::sort(rhsSorted.begin(), rhsSorted.end(), comparePoints);

    int diffX = lhsSorted[0].x - rhsSorted[0].x;
    int diffY = lhsSorted[0].y - rhsSorted[0].y;

    for (size_t i = 0; i < lhsSorted.size(); i++)
    {
      Point translatedPoint = translatePoint(rhsSorted[i], diffX, diffY);
      if (!(lhsSorted[i] == translatedPoint))
      {
        return false;
      }
    }
    return true;
  }
}
