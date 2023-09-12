#include "commanddict.h"
#include <stdexcept>

azheganova::Commands::Commands():
  dict_1(initializeDict1()),
  dict_2(initializeDict2()),
  dict_3(initializeDict3())
{}
void azheganova::Commands::doCommand(std::string command, std::vector< Polygon > & polygon, std::ostream & out, std::istream & in)
{
  try
  {
    dict_3.at(command)(polygon, out, in);
    return;
  }
  catch (const std::out_of_range & e)
  {}
  try
  {
    dict_1.at(command)(polygon, out);
    return;
  }
  catch (const std::out_of_range & e)
  {}
  auto spaceIndex = command.find(' ');
  auto index = std::stoull(command.substr(spaceIndex));
  dict_2.at(command.substr(0, spaceIndex))(polygon, index, out);
}
std::map< std::string, azheganova::Commands::command1_t > azheganova::Commands::initializeDict1()
{
  std::map< std::string, command1_t > dict;
  dict["AREA EVEN"] = getAreaEven;
  dict["AREA ODD"] = getAreaOdd;
  dict["AREA MEAN"] = getAreaMean;
  dict["MAX AREA"] = getMaxArea;
  dict["MAX VERTEXES"] = getMaxVertexes;
  dict["MIN AREA"] = getMinArea;
  dict["MIN VERTEXES"] = getMinVertexes;
  dict["COUNT EVEN"] = countEven;
  dict["COUNT ODD"] = countOdd;
  dict["RIGHTSHAPES"] = getRightshapes;
  return dict;
}
std::map< std::string, azheganova::Commands::command2_t > azheganova::Commands::initializeDict2()
{
  std::map< std::string, command2_t > dict;
  dict["AREA"] = getAreaNumOfVertexes;
  dict["COUNT"] = countNumOfVertexes;
  return dict;
}
std::map< std::string, azheganova::Commands::command3_t > azheganova::Commands::initializeDict3()
{
  std::map< std::string, command3_t > dict;
  dict["RMECHO"] = getRmecho;
  return dict;
}
