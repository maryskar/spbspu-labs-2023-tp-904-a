#include "command_system.h"
#include <iostream>
#include "commands.h"

namespace kumachev {

  CommandSystem createCommandSystem()
  {
    CommandSystem cs;
    cs.dict1.insert({ "AREA EVEN", areaEven });
    cs.dict1.insert({ "AREA ODD", areaOdd });
    cs.dict1.insert({ "AREA MEAN", areaMean });
    cs.dict1.insert({ "MAX AREA", maxArea });
    cs.dict1.insert({ "MAX VERTEXES", maxVert });
    cs.dict1.insert({ "MIN AREA", minArea });
    cs.dict1.insert({ "MIN VERTEXES", minVert });
    cs.dict1.insert({ "COUNT EVEN", countEven });
    cs.dict1.insert({ "COUNT ODD", countOdd });

    cs.dict2.insert({ "AREA", areaVertex });
    cs.dict2.insert({ "COUNT", countVert });

    cs.dict3.insert({ "ECHO", echo });
    cs.dict3.insert({ "RMECHO", rmEcho });

    return cs;
  }

  void printInvalid(std::ostream &ostream)
  {
    ostream << "<INVALID COMMAND>";
  }

  std::string inputCommand(std::istream &istream)
  {
    std::string command;
    istream >> command;

    if (!istream) {
      throw std::runtime_error("EOF reached");
    }

    if (command == "ECHO" || command == "RMECHO") {
      return command;
    }

    std::string param;
    istream >> param;

    if (!istream) {
      throw std::logic_error("Invalid command");
    }

    command += " ";
    command += param;
    return command;
  }

  void handleCommand(const std::string &commandName,
      std::vector< Polygon > &polygons, std::istream &istream,
      std::ostream &ostream)
  {
  }
}
