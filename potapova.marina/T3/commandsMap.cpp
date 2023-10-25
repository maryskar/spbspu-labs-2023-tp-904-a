#include "commandsMap.h"
#include <algorithm>
#include "commands.h"
#include "workWithIO.h"

namespace
{
  potapova::NotChangingCommandsMap getAreaCommands()
  {
    return potapova::NotChangingCommandsMap
    {
      {"EVEN", potapova::printSumOfSpecificAreas< potapova::ParityFlags::EVEN >},
      {"ODD", potapova::printSumOfSpecificAreas< potapova::ParityFlags::ODD >},
      {"MEAN", potapova::printAverageArea},
    };
  }

  template< potapova::GetExtremeElemFunc GetExtremeElem >
  potapova::NotChangingCommandsMap getExtremeCharacteristicCommands()
  {
    return potapova::NotChangingCommandsMap
    {
      {"AREA", potapova::printExtremeArea< GetExtremeElem >},
      {"VERTEXES", potapova::printExtremePoints< GetExtremeElem >}
    };
  }

  potapova::NotChangingCommandsMap getCountCommands()
  {
    return potapova::NotChangingCommandsMap
    {
      {"ODD", potapova::printPolygonsCountWithSpecificPointsNum< potapova::ParityFlags::ODD >},
      {"EVEN", potapova::printPolygonsCountWithSpecificPointsNum< potapova::ParityFlags::EVEN >}
    };
  }

  void runCommandFromMap(const potapova::NotChangingCommandsMap& commands,
      const std::string& command_mode,
      const std::deque< potapova::Polygon >& polygons,
      std::istream& in,
      std::ostream& out)
  {
      potapova::NotChangingCommandsMap::const_iterator command_ptr = commands.find(command_mode);
      if (command_ptr == commands.cend())
      {
        throw std::logic_error("There are no command");
      }
      command_ptr->second(polygons, in, out);
  }

  void processCommands(const potapova::NotChangingCommandsMap& commands,
      const std::deque< potapova::Polygon >& polygons,
      std::istream& in,
      std::ostream& out)
  {
    if (in.rdbuf()->sgetc() == '\n')
    {
      throw std::logic_error("There are no polygons");
    }
    std::string command_mode;
    in >> command_mode;
    runCommandFromMap(commands, command_mode, polygons, in, out);
  }

  template< void(*FuncWithNumArg)(const std::deque< potapova::Polygon >&, size_t, std::istream&, std::ostream&) >
  void processCommandsWithNumVar(const potapova::NotChangingCommandsMap& commands,
      const std::deque< potapova::Polygon >& polygons,
      std::istream& in,
      std::ostream& out)
  {
    if (in.rdbuf()->sgetc() == '\n')
    {
      throw std::logic_error("There are no polygons");
    }
    std::string command_mode;
    in >> command_mode;
    if (std::isdigit(command_mode.front()))
    {
      size_t target_count_points = 0;
      try
      {
        target_count_points = static_cast< size_t >(std::stoull(command_mode));
      }
      catch (const std::exception&)
      {
        throw std::logic_error("Invalid number");
      }
      FuncWithNumArg(polygons, target_count_points, in, out);
      return;
    }
    runCommandFromMap(commands, command_mode, polygons, in, out);
  }
}

  using ConstPolygonsRef = const std::deque< potapova::Polygon >&;
  potapova::CommandFunc< ConstPolygonsRef > getCommandWithModes(
      void(*processCommands)(const potapova::NotChangingCommandsMap&, ConstPolygonsRef, std::istream&, std::ostream&),
      const potapova::NotChangingCommandsMap& modes)
  {
    using namespace std::placeholders;
    return std::bind(processCommands, modes, _1, _2, _3);
  }

potapova::NotChangingCommandsMap potapova::getNonChangingCommands()
{
  return NotChangingCommandsMap
  {
    {"AREA", getCommandWithModes(processCommandsWithNumVar< printSumOfAreasWithSpecificPointsNum >, getAreaCommands())},
    {"MAX", getCommandWithModes(processCommands, getExtremeCharacteristicCommands< std::max_element >())},
    {"MIN", getCommandWithModes(processCommands, getExtremeCharacteristicCommands< std::min_element >())},
    {"COUNT", getCommandWithModes(processCommandsWithNumVar< printPolygonsNumWithTargetPointsNum >, getCountCommands())},
    {"INFRAME", printIsPolygonInFrame}
  };
}

potapova::ChangingCommandsMap potapova::getChangingCommands()
{
  return ChangingCommandsMap
  {
    {"RMECHO", removePolygonDuplicates}
  };
}
