#include "polygon.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>
#include "iofmtguard.hpp"
#include "typesio.hpp"

namespace gulyaev
{
  std::istream &operator>>(std::istream &in, Point &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    using sep = DelimiterIO;
    in >> sep{' '} >> sep{'('} >> dest.x >> sep{';'} >> dest.y >> sep{')'};
    return in;
  }
  std::istream &operator>>(std::istream &in, Polygon &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    Polygon input;
    {
      int number_of_vertices = 0;
      in >> number_of_vertices;
      iofmtguard fmtguard(in);
      in.unsetf(std::ios::skipws);
      if (in && (number_of_vertices > 2)) {
        input.points.reserve(number_of_vertices);
        std::copy_n(std::istream_iterator< Point >(in),
            number_of_vertices,
            std::back_inserter(input.points)
        );
      } else {
        in.setstate(std::ios::failbit);
      }
    }
    if (in) {
      std::string check;
      std::getline(in, check, '\n');
      if (in.eof()) {
        in.clear();
      }
      if (check.find_first_not_of(' ') != std::string::npos) {
        in.setstate(std::ios::failbit);
      } else {
        std::swap(dest,input);
      }
    }
    return in;
  }

  bool operator==(const Point &lhs,const Point &rhs)
  {
    return ((lhs.x == rhs.x && lhs.y == rhs.y) || (lhs.x == rhs.y && lhs.y == rhs.x));
  }
  std::size_t getSize(const Polygon &pol)
  {
    return pol.points.size();
  }

  double calc(const Point &lhs, const Point &rhs)
  {
    return (lhs.x * rhs.y - lhs.y * rhs.x);
  }
  double side(const Point &lhs, const Point &rhs)
  {
    double res = std::pow(rhs.x - lhs.x, 2) + std::pow(rhs.y - lhs.y, 2);
    return res;
  }
  bool rightAngle(const Point &lhs, const Point &mhs, const Point &rhs)
  {
    if ((side(lhs, mhs) + side(mhs, rhs)) == side(lhs, rhs)) {
      return true;
    }
    return false;
  }

  double getArea(const Polygon &pol)
  {
    std::vector< int > calcs;
    calcs.reserve(getSize(pol) - 1);
    std::transform(pol.points.cbegin(),
        --pol.points.cend(),
        ++pol.points.cbegin(),
        std::back_inserter(calcs),
        calc
    );
    double area = std::accumulate(calcs.cbegin(), calcs.cend(), 0);
    area += calc(pol.points.at(getSize(pol) - 1), pol.points.at(0));
    return std::abs(area / 2);
  }
  bool checkPermutation(const Polygon &lhs, const Polygon &rhs)
  {
    if (getSize(lhs) != getSize(rhs)) {
      return false;
    }
    bool res = std::is_permutation(std::cbegin(lhs.points),
        std::cend(lhs.points),
        std::cbegin(rhs.points)
    );
    return res;
  }
  bool checkRightShape(const Polygon &pol)
  {
    std::vector< Point > coordinates;
    coordinates.reserve(getSize(pol) + 2);
    coordinates.push_back(*(--pol.points.end()));
    std::copy(std::cbegin(pol.points), std::cend(pol.points), std::back_inserter(coordinates));
    coordinates.push_back(*pol.points.begin());
    for (std::size_t i = 1; i < (coordinates.size() - 1); ++i) {
      if (rightAngle(coordinates.at(i - 1), coordinates.at(i), coordinates.at(i + 1))) {
        return true;
      }
    }
    return false;
  }
}
