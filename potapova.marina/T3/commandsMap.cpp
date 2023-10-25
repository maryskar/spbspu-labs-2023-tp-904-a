#include "commandsMap.h"
#include <algorithm>
#include "commands.h"
#include "workWithIO.h"

namespace
{
  potapova::NotChangingCommansMap getAreaCommands()
  {
    return potapova::NotChangingCommansMap
    {
      {"EVEN", potapova::printSumOfSpecificAreas< potapova::EVEN >},
      {"ODD", potapova::printSumOfSpecificAreas< potapova::ODD >},
      {"MEAN", potapova::printAverageArea},
    };
  }

  template< potapova::GetExtremeElemFunc GetExtremeElem >
  potapova::NotChangingCommansMap getExtremeCharacteristicCommands()
  {
    return potapova::NotChangingCommansMap
    {
      {"AREA", potapova::printExtremeArea< GetExtremeElem >},
      {"VERTEXES", potapova::printExtremePoints< GetExtremeElem >}
    };
  }

  potapova::NotChangingCommansMap getCountCommands()
  {
    return potapova::NotChangingCommansMap
    {
      {"ODD", potapova::printPolygonsCountWithSpecificPointsNum< potapova::ODD >},
      {"EVEN", potapova::printPolygonsCountWithSpecificPointsNum< potapova::EVEN >}
    };
  }

  void runCommandFromMap(const potapova::NotChangingCommansMap& commands,
      const std::string& command_mode,
      const std::deque< potapova::Polygon >& polygons,
      std::istream& in,
      std::ostream& out)
  {
      potapova::NotChangingCommansMap::const_iterator command_ptr = commands.find(command_mode);
      if (command_ptr == commands.cend())
      {
        throw std::logic_error("There are no command");
      }
      command_ptr->second(polygons, in, out);
  }

  void processCommands(const potapova::NotChangingCommansMap& commands,
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
  void processCommandsWithNumVar(const potapova::NotChangingCommansMap& commands,
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
  potapova::CommandFunc< ConstPolygonsRef > getComandWithModes(
      void(*processCommands)(const potapova::NotChangingCommansMap&, ConstPolygonsRef, std::istream&, std::ostream&),
      const potapova::NotChangingCommansMap& modes)
  {
    using namespace std::placeholders;
    return std::bind(processCommands, modes, _1, _2, _3);
  }

potapova::NotChangingCommansMap potapova::getNonChangingCommands()
{
  return NotChangingCommansMap
  {
    {"AREA", getComandWithModes(processCommandsWithNumVar< printSumOfAreasWithSpecificPointsNum >, getAreaCommands())},
    {"MAX", getComandWithModes(processCommands, getExtremeCharacteristicCommands< std::max_element >())},
    {"MIN", getComandWithModes(processCommands, getExtremeCharacteristicCommands< std::min_element >())},
    {"COUNT", getComandWithModes(processCommandsWithNumVar< printPolygonsNumWithTargetPointsNum >, getCountCommands())},
    {"INFRAME", printIsPolygonInFrame}
  };
}

potapova::ChangingCommansMap potapova::getChangingCommands()
{
  return ChangingCommansMap
  {
    {"RMECHO", removePolygonDuplicates}
  };
}
