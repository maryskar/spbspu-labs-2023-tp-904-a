#ifndef SPBSPU_LABS_2023_TP_904_COMMANDS_H
#define SPBSPU_LABS_2023_TP_904_COMMANDS_H
#include <ostream>
#include "polygon.h"
namespace dimkashelk
{
  void printAreaEven(const std::vector< Polygon > &polygon, std::ostream &out);
  void printAreaOdd(const std::vector< Polygon > &polygon, std::ostream &out);
  void printAreaMean(const std::vector< Polygon > &polygon, std::ostream &out);
  void printAreaNumOfVertex(const std::vector< Polygon > &polygon, std::ostream &out, size_t num);
  void printMaxArea(const std::vector< Polygon > &polygon, std::ostream &out);
  void printMaxVertex(const std::vector< Polygon > &polygon, std::ostream &out);
  void printMinArea(const std::vector< Polygon > &polygon, std::ostream &out);
  void printMinVertex(const std::vector< Polygon > &polygon, std::ostream &out);
  void printCountEven(const std::vector< Polygon > &polygon, std::ostream &out);
  void printCountOdd(const std::vector< Polygon > &polygon, std::ostream &out);
  void printCountNumOfVertex(const std::vector< Polygon > &polygon, std::ostream &out, size_t num);
  void printSame(const std::vector< Polygon > &polygon, std::ostream &out, std::istream &in);
  void printIntersections(const std::vector< Polygon > &polygon, std::ostream &out, std::istream &in);
}
#endif
