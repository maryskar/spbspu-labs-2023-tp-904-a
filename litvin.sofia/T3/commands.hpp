#ifndef T3_COMMANDS_HPP
#define T3_COMMANDS_HPP
#include <map>
#include "polygon.hpp"
namespace litvin
{
  struct command_dicts_t
  {
    using signature_type_1 = void (*)(const std::vector< Polygon > & data, std::ostream & out);
    using signature_type_2 = void (*)(const std::vector< Polygon > & data, const Polygon & pol, std::ostream & out);
    using signature_type_3 = void (*)(const std::vector< Polygon > & data, size_t num, std::ostream & out);
    std::map< std::string, signature_type_1 > dict1;
    std::map< std::string, signature_type_2 > dict2;
    std::map< std::string, signature_type_3 > dict3;
    command_dicts_t();
    void executeCommand(const std::string & cmd, const std::vector< Polygon > & data, std::ostream & out) const;
    void executeCommand(const std::string & cmd,
        const std::vector< Polygon > & data,
        const Polygon & pol,
        std::ostream & out) const;
    void executeCommand(const std::string & cmd,
        const std::vector< Polygon > & data,
        size_t num,
        std::ostream & out) const;
  };
  void printInvalidCommand(std::ostream & out);
  std::string inputCommand(std::istream & in);
  void runCommand(const std::vector< Polygon > & data,
      const command_dicts_t & dicts,
      const std::string & cmd,
      std::ostream & out,
      std::istream & in);
  bool isEven(const Polygon & polygon);
  bool isOdd(const Polygon & polygon);
  void printEvenArea(const std::vector< litvin::Polygon > & data, std::ostream & out);
  void printOddArea(const std::vector< litvin::Polygon > & data, std::ostream & out);
  void printAverageArea(const std::vector< litvin::Polygon > & data, std::ostream & out);
  bool hasQuantityOfVertexes(const Polygon & pol, size_t num);
  double calcAreaIfNVertexes(const Polygon & pol, size_t number_of_vertexes);
  void printAreaIfNumberOfVertexesIs(const std::vector< litvin::Polygon > & data,
      size_t number_of_vertexes,
      std::ostream & out);
  double getMaxOrMinAreaOrVertexes(const std::vector< litvin::Polygon > & data, bool isTheGreatest, bool isArea);
  void printIfMaxArea(const std::vector< litvin::Polygon > & data, std::ostream & out);
  void printIfMaxVertexes(const std::vector< litvin::Polygon > & data, std::ostream & out);
  void printIfMinArea(const std::vector< litvin::Polygon > & data, std::ostream & out);
  void printIfMinVertexes(const std::vector< litvin::Polygon > & data, std::ostream & out);
  size_t countIf(bool (* predicate)(const Polygon & pol), const std::vector< litvin::Polygon > & data);
  void printNumOfEven(const std::vector< litvin::Polygon > & data, std::ostream & out);
  void printNumOfOdd(const std::vector< litvin::Polygon > & data, std::ostream & out);
  bool countIfNVertexes(const Polygon & pol, size_t num);
  void printNumOfPolygonsWithNumOfVertexes(const std::vector< litvin::Polygon > & data,
      size_t number_of_vertexes,
      std::ostream & out);
  bool areLinesIntersected(const Point & l1_p1, const Point & l1_p2, const Point & l2_p1, const Point & l2_p2);
  bool arePolygonsIntersected(const Polygon & pol1, const Polygon & pol2);
  void printNumberOfIntersections(const std::vector< litvin::Polygon > & data, const Polygon & pol, std::ostream & out);
  bool minmax_predicate(const Point & p1, const Point & p2);
  bool arePolygonsSame(const Polygon & polygon1, const Polygon & polygon2);
  void printNumberOfSameFigures(const std::vector< litvin::Polygon > & data, const Polygon & pol, std::ostream & out);
}
#endif
