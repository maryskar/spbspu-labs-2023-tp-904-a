#ifndef T3_NEW_COMMANDHANDLER_H
#define T3_NEW_COMMANDHANDLER_H

#include <functional>
#include <deque>
#include "Polygon.h"

namespace nesterov
{
  using const_cmd_t = std::function<
    void(const std::deque< Polygon > &,
         std::istream &,
         std::ostream &,
         std::ostream &
    )
  >;
  using cmd_t = std::function<
    void(std::deque< Polygon > &,
         std::istream &,
         std::ostream &,
         std::ostream &
    )
  >;

  void executeAreaCommand(const std::deque< Polygon > &pls,
                          std::istream &in,
                          std::ostream &out,
                          std::ostream &err);

  void executeMaxCommand(const std::deque< Polygon > &pls,
                         std::istream &in,
                         std::ostream &out,
                         std::ostream &err);

  void executeMinCommand(const std::deque< Polygon > &pls,
                         std::istream &in,
                         std::ostream &out,
                         std::ostream &err);

  void executeCountCommand(const std::deque< Polygon > &pls,
                           std::istream &in,
                           std::ostream &out,
                           std::ostream &err);

  void executeMaxSeqCommand(const std::deque< Polygon > &pls,
                            std::istream &in,
                            std::ostream &out,
                            std::ostream &err);

  void executeEchoCommand(std::deque< Polygon > &pls,
                          std::istream &in,
                          std::ostream &out,
                          std::ostream &err);

  void printAreaEven(const std::deque< Polygon > &pls,
                     std::ostream &out);

  void printAreaOdd(const std::deque< Polygon > &pls,
                    std::ostream &out);

  void printAreaMean(const std::deque< Polygon > &pls,
                     std::ostream &out);

  void printAreaWithVertexes(const std::deque< Polygon > &pls,
                             std::ostream &out,
                             size_t vertexes);

  void printMaxVertexes(const std::deque< Polygon > &pls,
                        std::ostream &out);

  void printMaxArea(const std::deque< Polygon > &pls,
                    std::ostream &out);

  void printMinVertexes(const std::deque< Polygon > &pls,
                        std::ostream &out);

  void printMinArea(const std::deque< Polygon > &pls,
                    std::ostream &out);

  void countEven(const std::deque< Polygon > &pls,
                 std::ostream &out);

  void countOdd(const std::deque< Polygon > &pls,
                std::ostream &out);

  void countWithNVertexes(const std::deque< Polygon > &pls,
                          std::ostream &out,
                          size_t vertexes);

  bool hasEvenVertexes(const Polygon &polygon);

  bool hasOddVertexes(const Polygon &polygon);

  double getArea(const Polygon &polygon);

  size_t getVertexes(const Polygon &polygon);

  bool hasNVertexes(const Polygon &polygon, size_t vertexes);

  double getAreaFun(double area, const Polygon &polygon);

  double getAreaOddFun(double area, const Polygon &polygon);

  double getAreaEvenFun(double area, const Polygon &polygon);

  double getAreaWithVertexesFun(double area, const Polygon &polygon, size_t vertexes);

  double getAreaHelper(const Point &point1, const Point &point2);
}

#endif
