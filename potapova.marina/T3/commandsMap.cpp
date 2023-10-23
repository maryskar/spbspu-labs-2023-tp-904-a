#include "commandsMap.h"
#include <algorithm>
#include "commands.h"

namespace
{
  potapova::NotChangingCommansMap getAreaCommands()
  {
    return potapova::NotChangingCommansMap
    {
      {"EVEN", potapova::printSumOfSpecificAreas< potapova::EVEN >},
      {"ODD", potapova::printSumOfSpecificAreas< potapova::ODD >},
      {"MEAN", potapova::printAverageArea},
      {"NUM_OF_VERTEXES", potapova::printSumOfAreasWithSpecificPointsCounts}
    };
  }
}

namespace potapova
{
  NotChangingCommansMap getNonChangingCommands()
  {
    using namespace std::placeholders;

    return NotChangingCommansMap
    {
      {"AREA", std::bind(processAreaCommands, getAreaCommands(), _1, _2, _3, _4)},
      {"MAX AREA", printExtremeArea< std::max_element >},
      {"MAX VERTEXES", printExtremePoints< std::min_element >},
      {"MIN AREA", printExtremeArea< std::max_element >},
      {"MIN VERTEXES", printExtremePoints< std::min_element >},
      {"COUNT ODD", printPolygonsCountWithSpecificPointsNum< ODD >},
      {"COUNT EVEN", printPolygonsCountWithSpecificPointsNum< EVEN >},
      {"COUNT NUM_OF_VERTEXES", printPolygonsCountWithTargetPointsNum},
      {"INFRAME", printIsPolygonInFrame}
    };
  }

  ChangingCommansMap getChangingCommands()
  {
    return ChangingCommansMap
    {
      {"RMECHO", removePolygonDuplicates}
    };
  }
}
