#include "command_system.h"
#include <iostream>
#include "commands.h"
#include "basic_io.h"
#include "polygon_io.h"
#include "stream_guard.h"

namespace kumachev {
  static Polygon readPolygonParameter(std::istream &istream)
  {
    std::istream::sentry sentry(istream);
    StreamGuard guard(istream);
    istream >> std::noskipws;
    Polygon poly;
    istream >> poly >> CharIO{ '\n' };

    if (!istream) {
      throw std::logic_error("Invalid polygon value");
    }

    return poly;
  }

  CommandSystem::CommandSystem()
  {
    dict1_.insert({ "AREA EVEN", areaEven });
    dict1_.insert({ "AREA ODD", areaOdd });
    dict1_.insert({ "AREA MEAN", areaMean });
    dict1_.insert({ "MAX AREA", maxArea });
    dict1_.insert({ "MAX VERTEXES", maxVert });
    dict1_.insert({ "MIN AREA", minArea });
    dict1_.insert({ "MIN VERTEXES", minVert });
    dict1_.insert({ "COUNT EVEN", countEven });
    dict1_.insert({ "COUNT ODD", countOdd });

    dict2_.insert({ "AREA", areaVertex });
    dict2_.insert({ "COUNT", countVert });

    dict3_.insert({ "ECHO", echo });
    dict3_.insert({ "RMECHO", rmEcho });
  }

  const umap &CommandSystem::getDict1() const
  {
    return dict1_;
  }

  const umap_int &CommandSystem::getDict2() const
  {
    return dict2_;
  }

  const umap_poly &CommandSystem::getDict3() const
  {
    return dict3_;
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

  void handleCommand(const std::string &commandName, const CommandSystem &cmds,
      std::vector< Polygon > &polygons, std::istream &istream,
      std::ostream &ostream)
  {
    try {
      auto &handler = cmds.getDict1().at(commandName);
      handler(polygons, ostream);
      return;
    }
    catch (const std::out_of_range &e) {
    }

    try {
      auto &handler = cmds.getDict3().at(commandName);
      Polygon param = readPolygonParameter(istream);
      handler(polygons, param, ostream);
      return;
    }
    catch (const std::out_of_range &e) {
    }

    size_t delim = commandName.find(' ');
    std::string cmd = commandName.substr(0, delim);
    size_t parameter = std::stoull(commandName.substr(delim));

    if (parameter < 3) {
      throw std::logic_error("Vertex count must more than 2");
    }

    auto &handler = cmds.getDict2().at(cmd);
    handler(polygons, parameter, ostream);
  }
}
