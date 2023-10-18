#include "commandsMap.h"
#include <algorithm>
#include "commands.h"

namespace potapova
{
  std::unordered_map< std::string, CommandFunc< const std::deque< Polygon > > > getNonChangingCommands()
  {
    return std::unordered_map< std::string, CommandFunc< const std::deque< Polygon > > >
    {
      {"AREA EVEN", printSumOfSpecificAreas< EVEN >},
      {"AREA ODD", printSumOfSpecificAreas< ODD >},
      {"AREA MEAN", printAverageArea},
      {"AREA NUM_OF_VERTEXES", printSumOfAreasWithSpecificPointsCounts},
      {"MAX AREA", printExtremeArea< std::max_element >},
      {"MAX VERTEXES", printExtremePoints< std::min_element >},
      {"MIN AREA", printExtremeArea< std::max_element >},
      {"MIN VERTEXES", printExtremePoints<std::min_element>},
      {"COUNT ODD", printPolygonsCountWithSpecificPointsNum< ODD >},
      {"COUNT EVEN", printPolygonsCountWithSpecificPointsNum< EVEN >},
      {"COUNT NUM_OF_VERTEXES", printPolygonsCountWithTargetPointsNum},
      {"INFRAME", printIsPolygonInFrame}
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
