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

  CommandSystem::CommandSystem(std::istream &istream, std::ostream &ostream,
      const std::vector< Polygon > &polygons):
    istream_(istream),
    ostream_(ostream),
    polygons_(polygons)
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

  void printInvalid(std::ostream &ostream)
  {
    ostream << "<INVALID COMMAND>";
  }

  std::string CommandSystem::inputCommand()
  {
    std::string command;
    istream_ >> command;

    if (!istream_) {
      throw std::runtime_error("EOF reached");
    }

    if (command == "ECHO" || command == "RMECHO") {
      return command;
    }

    std::string param;
    istream_ >> param;

    if (!istream_) {
      throw std::logic_error("Invalid command");
    }

    command += " ";
    command += param;
    return command;
  }

  void CommandSystem::handleCommand(const std::string &commandName)
  {
    try {
      auto &handler = dict1_.at(commandName);
      handler(polygons_, ostream_);
      return;
    }
    catch (const std::out_of_range &e) {
    }

    try {
      auto &handler = dict3_.at(commandName);
      Polygon param = readPolygonParameter(istream_);
      handler(polygons_, param, ostream_);
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

    auto &handler = dict2_.at(cmd);
    handler(polygons_, parameter, ostream_);
  }
}
