#ifndef DICTIONARYCOMMAND_H
#define DICTIONARYCOMMAND_H

#include <string>
#include <map>

#include "command.h"

namespace aristarkhov
{
  class Commands
  {
  public:
    Commands();
    void doConstCommand(const std::vector< Polygon >& polygons, const std::string& cmd, std::ostream& out) const;
    void doCommandInput(const std::vector< Polygon >& polygons, const std::string& cmd, size_t count, std::ostream& out) const;
    void doCommandPolygon(std::vector< Polygon >& polygons, const std::string& cmd, const Polygon& polygon, std::ostream& out) const;

  private:
    using FirstType = void (*)(const std::vector< Polygon >& polygons, std::ostream& out);
    using SecondType = void (*)(const std::vector< Polygon >& polygons, size_t count, std::ostream& out);
    using ThirdType = void (*)(std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out);
    std::map< std::string, FirstType  > dict1;
    std::map< std::string, SecondType > dict2;
    std::map< std::string, ThirdType  > dict3;
  };

  std::string getCommand(std::istream& in);
  std::string cutString(std::string& string);
  void doCommand(std::vector< Polygon >& polygons, const Commands& dict, std::string& cmd, std::ostream& out, std::istream& in);
}

#endif
