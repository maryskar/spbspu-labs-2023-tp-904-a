#ifndef SPBSPU_LABS_2023_TP_904_COMMANDS_H
#define SPBSPU_LABS_2023_TP_904_COMMANDS_H
#include <ostream>
#include "polygon.h"
using polygon = dimkashelk::Polygon;
using v_polygon = std::vector< polygon >;
using point = dimkashelk::Point;
namespace dimkashelk
{
  void printAreaEven(const v_polygon &polygon, std::ostream &out);
  void printAreaOdd(const v_polygon &polygon, std::ostream &out);
  void printAreaMean(const v_polygon &polygon, std::ostream &out);
  void printAreaNumOfVertex(const v_polygon &polygon, std::ostream &out, size_t num);
  void printMaxArea(const v_polygon &polygon, std::ostream &out);
  void printMaxVertex(const v_polygon &polygon, std::ostream &out);
  void printMinArea(const v_polygon &polygon, std::ostream &out);
  void printMinVertex(const v_polygon &polygon, std::ostream &out);
  void printCountEven(const v_polygon &polygon, std::ostream &out);
  void printCountOdd(const v_polygon &polygon, std::ostream &out);
  void printCountNumOfVertex(const v_polygon &polygon, std::ostream &out, size_t num);
  void printSame(const v_polygon &polygon, std::ostream &out, std::istream &in);
  void printIntersections(const v_polygon &polygon, std::ostream &out, std::istream &in);
}
#endif
