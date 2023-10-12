#include "commandsMap.h"
#include <functional>
#include "commands.h"

namespace potapova
{
  std::unordered_map< std::string, commandFunc >
  non_changing_commands =
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
    {"COUNT NUM_OF_VERTEXES", countPolygonsWithPointsNum}
  };

  std::unordered_map< std::string, commandFunc >
  changing_commands =
  {
    {"RMECHO", removePolygonDuplicates},
    {"INFRAME", checkPolygonInFrame}
  };
}
