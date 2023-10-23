#ifndef DICTIONARYCOMMAND_H
#define DICTIONARYCOMMAND_H

#include <map>
#include "polygon.h"

namespace aristarkhov
{
  class Commands
  {
  public:

  private:
    using FirstType = void (*)(const std::vector< Polygon >& polygons, std::ostream& out);
    using SecondType = void (*)(const std::vector< Polygon >& polygons, size_t count, std::ostream& out);
    using ThirdType = void (*)(std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out);
    std::map< std::string, FirstType  > dict1;
    std::map< std::string, SecondType > dict2;
    std::map< std::string, ThirdType  > dict3;
  };

}
#endif