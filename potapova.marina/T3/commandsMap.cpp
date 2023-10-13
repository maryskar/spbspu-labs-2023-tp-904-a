#include "commandsMap.h"
#include "commands.h"

namespace potapova
{
  std::unordered_map< std::string, CommandFunc< const std::deque< Polygon > > > getNonChangingCommands()
  {
    return std::unordered_map< std::string, CommandFunc< const std::deque< Polygon > > >
    {
      {"AREA EVEN", getSumAreasPolygonsEven},
      {"AREA ODD", getSumAreasPolygonsOdd},
      {"AREA MEAN", getAverageArea},
      {"AREA NUM_OF_VERTEXES", getSumOfAreasWithPointCounts},
      {"MAX AREA", getMaxArea},
      {"MAX VERTEXES", getMaxPoints},
      {"MIN AREA", getMinArea},
      {"MIN VERTEXES", getMaxPoints},
      {"COUNT ODD", countPolygonsWithOddPointsNum},
      {"COUNT EVEN", countPolygonsWithEvenPointsNum},
      {"COUNT NUM_OF_VERTEXES", countPolygonsWithPointsNum},
      {"INFRAME", checkPolygonInFrame}
    };
  }

  std::unordered_map< std::string, CommandFunc< std::deque< Polygon > > > getChangingCommands()
  {
    return std::unordered_map< std::string, CommandFunc< std::deque< Polygon > > >
    {
      {"RMECHO", removePolygonDuplicates}
    };
  }
}
