#ifndef T3_COMMANDS_HPP
#define T3_COMMANDS_HPP
#include "polygon.hpp"
namespace litvin
{
  bool isEven(const Polygon & polygon);
  bool isOdd(const Polygon & polygon);
  void printEvenArea(const std::vector< Polygon > & data, std::ostream & out);
  void printOddArea(const std::vector< Polygon > & data, std::ostream & out);
  void printAverageArea(const std::vector< Polygon > & data, std::ostream & out);
  bool hasQuantityOfVertexes(const Polygon & pol, size_t num);
  double calcAreaIfNVertexes(const Polygon & pol, size_t number_of_vertexes);
  void printAreaIfNumberOfVertexesIs(const std::vector< Polygon > & data,
      size_t number_of_vertexes,
      std::ostream & out);
  double getMaxOrMinAreaOrVertexes(const std::vector< Polygon > & data, bool isTheGreatest, bool isArea);
  void printIfMaxArea(const std::vector< Polygon > & data, std::ostream & out);
  void printIfMaxVertexes(const std::vector< Polygon > & data, std::ostream & out);
  void printIfMinArea(const std::vector< Polygon > & data, std::ostream & out);
  void printIfMinVertexes(const std::vector< Polygon > & data, std::ostream & out);
  size_t countIf(bool (* predicate)(const Polygon & pol), const std::vector< Polygon > & data);
  void printNumOfEven(const std::vector< Polygon > & data, std::ostream & out);
  void printNumOfOdd(const std::vector< Polygon > & data, std::ostream & out);
  bool countIfNVertexes(const Polygon & pol, size_t num);
  void printNumOfPolygonsWithNumOfVertexes(const std::vector< Polygon > & data,
      size_t number_of_vertexes,
      std::ostream & out);
  bool areLinesIntersected(const Point & l1_p1, const Point & l1_p2, const Point & l2_p1, const Point & l2_p2);
  bool arePolygonsIntersected(const Polygon & pol1, const Polygon & pol2);
  void printNumberOfIntersections(const std::vector< Polygon > & data, const Polygon & pol, std::ostream & out);
  bool minmax_predicate(const Point & p1, const Point & p2);
  bool arePolygonsSame(const Polygon & polygon1, const Polygon & polygon2);
  void printNumberOfSameFigures(const std::vector< Polygon > & data, const Polygon & pol, std::ostream & out);
}
#endif
