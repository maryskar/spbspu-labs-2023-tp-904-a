#include "commands_dict.h"
#include <string>
#include "functions.h"

namespace kryuchkova
{
  CommandDict::CommandDict():
    simple_comm_(initSimpleComm()),
    input_comm_(initInputComm()),
    size_comm_(initSizeComm())
  {}

  void CommandDict::handleCommand(std::string comm, const std::vector< Polygon > & pol, std::ostream & out, std::istream & in)
  {
    try
    {
      input_comm_.at(comm)(pol, out, in);
      return;
    }
    catch(const std::out_of_range & e)
    {}
    try
    {
      simple_comm_.at(comm)(pol, out);
      return;
    }
    catch(const std::out_of_range & e)
    {}
    auto spaceIndex = comm.find(' ');
    auto index = std::stoull(comm.substr(spaceIndex));
    size_comm_.at(comm.substr(0, spaceIndex))(pol, out, index);
  }

  std::map< std::string, CommandDict::comm_t > CommandDict::initSimpleComm()
  {
    std::map< std::string, comm_t > dict;
    dict["AREA EVEN"] = printAreaEven;
    dict["AREA ODD"] = printAreaOdd;
    dict["AREA MEAN"] = printAreaMean;
    dict["MAX AREA"] = printMaxArea;
    dict["MAX VERTEXES"] = printMaxVer;
    dict["MIN AREA"] = printMinArea;
    dict["MIN VERTEXES"] = printMinVer;
    dict["COUNT EVEN"] = printCountEven;
    dict["COUNT ODD"] = printCountOdd;
    dict["RIGHTSHAPES"] = printRightShapes;
    return dict;
  }
  std::map< std::string, CommandDict::comm_size_t > CommandDict::initSizeComm()
  {
    std::map< std::string, comm_size_t > dict;
    dict["AREA"] = printAreaNumOfVer;
    dict["COUNT"] = printCountNumOfVer;
    return dict;
  }
  std::map< std::string, CommandDict::comm_input_t > CommandDict::initInputComm()
  {
    std::map< std::string, comm_input_t > dict;
    dict["SAME"] = printSame;
    return dict;
  }
}
