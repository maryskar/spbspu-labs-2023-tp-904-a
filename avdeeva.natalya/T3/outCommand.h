#ifndef SPBSPU_LABS_2023_TP_904_A_OUTCOMMAND_H
#define SPBSPU_LABS_2023_TP_904_A_OUTCOMMAND_H
#include <deque>
#include "polygon.h"
namespace avdeeva
{
  void areaCommand(const std::deque< Polygon > & polygons, std::istream & in, std::ostream & out);
  void maxCommand(const std::deque< Polygon > & polygons, std::istream & in, std::ostream & out);
  void minCommand(const std::deque< Polygon > & polygons, std::istream & in, std::ostream & out);
  void countCommand(const std::deque< Polygon > & polygons, std::istream & in, std::ostream & out);
  void rightshapesCommand(const std::deque< Polygon > & polygons, std::istream & in, std::ostream & out);
  void inframeCommand(const std::deque< Polygon > & polygons, std::istream & in, std::ostream & out);
}
#endif
