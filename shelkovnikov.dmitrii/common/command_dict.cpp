#include "command_dict.h"
#include "commands.h"
using container = dimkashelk::CommandContainer;
container::CommandContainer():
  dict_simple_command_(initializeSimpleCommand()),
  dict_with_size_t_command_(initializeSizeTCommand()),
  dict_with_input_command_(initializeInputCommand())
{}
void container::doCommand(std::string command, const std::vector< Polygon > &data, std::ostream &out, std::istream &in)
{
  try
  {
    dict_with_input_command_.at(command)(data, out, in);
    return;
  }
  catch (const std::out_of_range &e)
  {}
  try
  {
    dict_simple_command_.at(command)(data, out);
    return;
  }
  catch (const std::out_of_range &e)
  {}
  auto spaceIndex = command.find(' ');
  auto index = std::stoull(command.substr(spaceIndex));
  dict_with_size_t_command_.at(command.substr(0, spaceIndex))(data, out, index);
}
std::map< std::string, container::comm_t > container::initializeSimpleCommand()
{
  std::map< std::string, comm_t > dic;
  dic["AREA EVEN"] = printAreaEven;
  dic["AREA ODD"] = printAreaOdd;
  dic["AREA MEAN"] = printAreaMean;
  dic["MAX AREA"] = printMaxArea;
  dic["MAX VERTEXES"] = printMaxVertex;
  dic["MIN AREA"] = printMinArea;
  dic["MIN VERTEXES"] = printMinVertex;
  dic["COUNT EVEN"] = printCountEven;
  dic["COUNT ODD"] = printCountOdd;
  return dic;
}
std::map< std::string, container::comm_with_size_t > container::initializeSizeTCommand()
{
  std::map< std::string, comm_with_size_t > dic;
  dic["AREA"] = printAreaNumOfVertex;
  dic["COUNT"] = printCountNumOfVertex;
  return dic;
}
std::map< std::string, container::comm_with_input_t > container::initializeInputCommand()
{
  std::map< std::string, comm_with_input_t > dic;
  dic["INTERSECTIONS"] = printIntersections;
  dic["SAME"] = printSame;
  return dic;
}
