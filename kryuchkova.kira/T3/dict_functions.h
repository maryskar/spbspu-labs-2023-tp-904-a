#ifndef DICT_FUNCTIONS_H
#define DICT_FUNCTIONS_H
#include <ostream>
#include "polygon.h"

namespace kryuchkova
{
  void printAreaEven(const std::vector< Polygon > & polygon, std::ostream & out);
  void printAreaOdd(const std::vector< Polygon > & polygon, std::ostream & out);
  void printAreaMean(const std::vector< Polygon > & polygon, std::ostream & out);
  void printAreaNumOfVer(const std::vector< Polygon > & polygon, std::ostream & out, size_t num);
  void printMaxArea(const std::vector< Polygon > & polygon, std::ostream & out);
  void printMaxVer(const std::vector< Polygon > & polygon, std::ostream & out);
  void printMinArea(const std::vector< Polygon > & polygon, std::ostream & out);
  void printMinVer(const std::vector< Polygon > & polygon, std::ostream & out);
  void printCountEven(const std::vector< Polygon > & polygon, std::ostream & out);
  void printCountOdd(const std::vector< Polygon > & polygon, std::ostream & out);
  void printCountNumOfVer(const std::vector< Polygon > & polygon, std::ostream & out, size_t num);
  void printRightShapes(const std::vector< Polygon > & polygon, std::ostream & out);
  void printSame(const std::vector< Polygon > & polygon, std::ostream & out, std::istream & in);

}

#endif
