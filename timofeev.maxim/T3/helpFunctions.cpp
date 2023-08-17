#include "helpFunctions.h"
#include <ostream>
#include <vector>
#include "polygon.h"
namespace timofeev
{
  bool is_number(const std::string& s)
  {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
  }
  void printError(std::ostream& out)
  {
    out << "<INVALID COMMAND>" << "\n";
  }

  bool isOdd(const Polygon& polygon)
  {
    return polygon.points.size() % 2;
  }

  bool isEven(const Polygon& polygon)
  {
    return !(isOdd(polygon));
  }
  void doEven(const std::vector< Polygon >& res)
  {

  }
  void doOdd(const std::vector< Polygon >& res);
  void doMaxArea(const std::vector< Polygon >& res);
  void doMaxV(const std::vector< Polygon >& res);
  void doMinArea(const std::vector< Polygon >& res);
  void doMinV(const std::vector< Polygon >& res);
  void doСountEven(const std::vector< Polygon >& res);
  void doCountOdd(const std::vector< Polygon >& res);


}