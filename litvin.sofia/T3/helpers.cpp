#include "helpers.hpp"
#include <iostream>
#include <iostructures.hpp>
#include "commands.hpp"
litvin::CommandDicts::CommandDicts()
{
  dict1.insert({"AREA EVEN", printEvenArea});
  dict1.insert({"AREA ODD", printOddArea});
  dict1.insert({"AREA MEAN", printAverageArea});
  dict1.insert({"MAX AREA", printIfMaxArea});
  dict1.insert({"MAX VERTEXES", printIfMaxVertexes});
  dict1.insert({"MIN VERTEXES", printIfMinVertexes});
  dict1.insert({"MIN AREA", printIfMinArea});
  dict1.insert({"COUNT EVEN", printNumOfEven});
  dict1.insert({"COUNT ODD", printNumOfOdd});
  dict2.insert({"INTERSECTIONS", printNumberOfIntersections});
  dict2.insert({"SAME", printNumberOfSameFigures});
  dict3.insert({"COUNT", printNumOfPolygonsWithNumOfVertexes});
  dict3.insert({"AREA", printAreaIfNumberOfVertexesIs});
}
std::ostream & litvin::printInvalidCommand(std::ostream & out)
{
  out << "<INVALID COMMAND>";
  return out;
}
std::string litvin::inputCommand(std::istream & in)
{
  std::string command_name = " ";
  in >> command_name;
  if (!in)
  {
    throw std::runtime_error("Command file ending were reached");
  }
  if (command_name != "SAME" && command_name != "INTERSECTIONS")
  {
    std::string parameter = " ";
    in >> parameter;
    if (!in)
    {
      throw std::invalid_argument("Invalid command parameter");
    }
    command_name = command_name + " " + parameter;
  }
  return command_name;
}
void litvin::CommandDicts::executeCommand(const std::string & cmd,
    const std::vector< Polygon > & data,
    std::ostream & out) const
{
  signature_type_1 function = dict1.at(cmd);
  function(data, out);
}
void litvin::CommandDicts::executeCommand(const std::string & cmd,
    const std::vector< Polygon > & data,
    const Polygon & pol,
    std::ostream & out) const
{
  signature_type_2 function = dict2.at(cmd);
  function(data, pol, out);
}
void litvin::CommandDicts::executeCommand(const std::string & cmd,
    const std::vector< Polygon > & data,
    size_t num,
    std::ostream & out) const
{
  signature_type_3 function = dict3.at(cmd);
  function(data, num, out);
}
void litvin::runCommand(const std::vector< Polygon > & data,
    const CommandDicts & dicts,
    const std::string & cmd,
    std::ostream & out,
    std::istream & in)
{
  if (cmd == "INTERSECTIONS" || cmd == "SAME")
  {
    Polygon polygon;
    in >> polygon >> DelimiterIO{'\n'};
    if (!in)
    {
      throw std::invalid_argument("Invalid command parameter");
    }
    try
    {
      dicts.executeCommand(cmd, data, polygon, out);
      return;
    }
    catch (const std::out_of_range & error)
    {}
  }
  try
  {
    dicts.executeCommand(cmd, data, out);
    return;
  }
  catch (const std::out_of_range & error)
  {}
  size_t pos = cmd.find(' ');
  size_t num = std::stoull(cmd.substr(pos));
  dicts.executeCommand(cmd.substr(0, pos), data, num, out);
}
