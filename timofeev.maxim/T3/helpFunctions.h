#ifndef T3_HELPFUNCTIONS_H
#define T3_HELPFUNCTIONS_H

#include <string>
#include <vector>
#include "polygon.h"
namespace timofeev
{
  bool is_number(const std::string& s);
  void printError(std::ostream &out);

  void doEven(const std::vector< Polygon >& res);
  void doOdd(const std::vector< Polygon >& res);
  void doMaxArea(const std::vector< Polygon >& res);
  void doMaxV(const std::vector< Polygon >& res);
  void doMinArea(const std::vector< Polygon >& res);
  void doMinV(const std::vector< Polygon >& res);
  void doСountEven(const std::vector< Polygon >& res);
  void doCountOdd(const std::vector< Polygon >& res);


}
#endif //T3_HELPFUNCTIONS_H
