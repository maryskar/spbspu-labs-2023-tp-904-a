#include "helpFunctions.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <limits>
#include <numeric>
#include "polygon.h"

namespace aksenov
{
  void outInvalidCommand(std::ostream &out)
  {
    out << "<INVALID COMMAND>" << "\n";
  }

  bool getShapes(std::vector< aksenov::Polygon > &shapesArray, std::string fileName)
  {
    std::ifstream in(fileName);
    if (!in.is_open())
    {
      std::cout << "cant open file" << "\n";
      return false;
    }
    while (!in.eof())
    {
      std::copy(std::istream_iterator< aksenov::Polygon >(in), std::istream_iterator< aksenov::Polygon >(), std::back_inserter(shapesArray));
      if (in.fail() && !in.eof())
      {
        in.clear();
        in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
    return true;
  }

  double calculate(const Point &p1, const Point &p2)
  {
    return p1.x * p2.y - p2.x * p1.y;
  }

  double calculateArea(const Polygon &p)
  {
    const std::vector< Point > &points = p.points;
    std::vector< double > products;
    std::transform(points.begin(), points.end(), std::next(points.begin()), std::back_inserter(products), calculate);
    double area = std::accumulate(products.begin(), products.end(), 0.0);
    return std::fabs(area / 2.0);
  }


  std::vector< double > getArea(const std::vector< Polygon > &pol)
  {
    std::vector< double > areas;
    std::transform(pol.begin(), pol.end(), std::back_inserter(areas), calculateArea);
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

  bool isEqual(const Polygon &pol, size_t amount)
  {
    return pol.points.size() == amount;
  }

  bool comparePoints(const Point &lhs, const Point &rhs)
  {
    if (lhs.x == rhs.x)
    {
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
    if (lhs.points.size() != rhs.points.size())
    {
      return false;
    }

    std::vector< Point > lhsSorted(lhs.points);
    std::vector< Point > rhsSorted(rhs.points);

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
