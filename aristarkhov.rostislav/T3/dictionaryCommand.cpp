#include "dictionaryCommand.h"

#include <iostream>
#include <iostruct.h>

#include "polygon.h"

aristarkhov::Commands::Commands()
{
  dict1.insert({ "AREA EVEN", areaEven });
  dict1.insert({ "AREA ODD", areaOdd });
  dict1.insert({ "AREA MEAN", areaMean });

  dict1.insert({ "MAX AREA", maxArea });
  dict1.insert({ "MAX VERTEXES", maxVertexes });
  dict1.insert({ "MIN AREA", minArea });
  dict1.insert({ "MIN VERTEXES", minVertexes });

  dict1.insert({ "COUNT EVEN", countEven });
  dict1.insert({ "COUNT ODD", countOdd });

  dict2.insert({ "AREA", areaVertexes });
  dict2.insert({ "COUNT", countVertexes });

  dict3.insert({ "RMECHO", rmEcho });
  dict3.insert({ "INFRAME", printInFrame });
}

void aristarkhov::Commands::doConstCommand(const std::vector< Polygon >& polygons,
    const std::string& cmd,
    std::ostream& out) const
{
  FirstType function = dict1.at(cmd);
  function(polygons, out);
}

void aristarkhov::Commands::doCommandInput(const std::vector< Polygon >& polygons,
    const std::string& cmd,
    size_t count,
    std::ostream& out) const
{
  SecondType function = dict2.at(cmd);
  function(polygons, count, out);
}

void aristarkhov::Commands::doCommandPolygon(std::vector< Polygon >& polygons,
    const std::string& cmd,
    const Polygon& polygon,
    std::ostream& out) const
{
  ThirdType function = dict3.at(cmd);
  function(polygons, polygon, out);
}

bool isSpecialCommand(std::string name)
{
  return name == "INFRAME" || name == "RMECHO";
}

std::string aristarkhov::getCommand(std::istream& in)
{
  std::string command = "";
  in >> command;
  if (!in)
  {
    throw std::runtime_error("problems with input");
  }

  if (!isSpecialCommand(command))
  {
    std::string cmdSubName = "";
    in >> cmdSubName;
    if (!in)
    {
      std::invalid_argument("invalid command parameter");
    }
    command += " " + cmdSubName;
  }

  return command;
}

std::string aristarkhov::cutString(std::string& string)
{
  std::string res = "";
  std::size_t pos = string.find(' ');

  if (pos != std::string::npos)
  {
    res = string.substr(0, pos);
    string.erase(0, pos + 1);

    return res;
  }
  else if (string != "")
  {
    res = string;
    string = "";

    return res;
  }
  else
  {
    throw std::invalid_argument("incorrect args");
  }
}

void aristarkhov::doCommand(std::vector< Polygon >& polygons,
    const Commands& dict,
    std::string& cmd,
    std::ostream& out,
    std::istream& in)
{
  if (isSpecialCommand(cmd))
  {
    Polygon polygon;
    in >> polygon >> DelimiterIO{'\n'};
    if (!in)
    {
      throw std::invalid_argument("Error polygon");
    }
    try
    {
      dict.doCommandPolygon(polygons, cmd, polygon, out);
      return;
    }
    catch (const std::out_of_range& error)
    {
    }
  }
  try
  {
    dict.doConstCommand(polygons, cmd, out);
    return;
  }
  catch (const std::out_of_range& error)
  {
  }

  std::string command = cutString(cmd);
  size_t count = std::stoull(cmd);

  dict.doCommandInput(polygons, command, count, out);
}
