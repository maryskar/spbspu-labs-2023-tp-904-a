#ifndef T3_HELPFUNCTIONS_H
#define T3_HELPFUNCTIONS_H
#include <string>
#include <vector>
#include "polygon.h"
namespace timofeev
{
  bool is_number(const std::string& s);
  void printError(std::ostream& out);

  void doEven(const std::vector< Polygon >& res);
  void doOdd(const std::vector< Polygon >& res);
  void doMaxArea(const std::vector< Polygon >& res);
  void doMaxV(const std::vector< Polygon >& res);
  void doMinArea(const std::vector< Polygon >& res);
  void doMinV(const std::vector< Polygon >& res);
  void doСountEven(const std::vector< Polygon >& res);
  void doCountOdd(const std::vector< Polygon >& res);
  void doMean(const std::vector< Polygon >& res);

  void doAreaV(const std::vector< Polygon >& res, size_t& val);
  void doCountV(const std::vector< Polygon >& res, size_t& val);

  bool isEqual(const Polygon &pol, size_t val);
  bool comparePolygons(const Polygon& a, const Polygon& b);
  bool isOdd(const Polygon &data);
  bool isEven(const Polygon &data);

  bool isAngle(const Polygon& pol);
  int operator*(const Point &p1, const Point &p2);

  double getCos(const Point &p1, const Point &p2, const Point &p3);
  double getArea(const std::vector<Polygon> &pol, std::vector< double > &indivAreas);
}
#endif //T3_HELPFUNCTIONS_H
