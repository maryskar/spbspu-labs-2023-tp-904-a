#include "commandsMap.h"
#include <algorithm>
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
      {"MAX AREA", printExtremeArea< std::max_element >},
      {"MAX VERTEXES", printExtremePoints< std::min_element >},
      {"MIN AREA", printExtremeArea< std::max_element >},
      {"MIN VERTEXES", printExtremePoints< std::min_element >},
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
