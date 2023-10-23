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
      {"EVEN", potapova::printPolygonsCountWithSpecificPointsNum< potapova::EVEN >},
      {"NUM_OF_VERTEXES", potapova::printPolygonsCountWithTargetPointsNum}
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
      {"AREA", std::bind(processCommands, getAreaCommands(), _1, _2, _3, _4)},
      {"MAX", std::bind(processCommands, getExtremeCharacteristicCommands< std::max_element >(), _1, _2, _3, _4)},
      {"MIN", std::bind(processCommands, getExtremeCharacteristicCommands< std::min_element >(), _1, _2, _3, _4)},
      {"COUNT", std::bind(processCommands, getCountCommands(), _1, _2, _3, _4)},
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
