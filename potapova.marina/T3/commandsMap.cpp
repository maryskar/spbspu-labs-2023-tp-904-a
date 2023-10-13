#include "commandsMap.h"
#include <functional>
#include <unordered_map>
#include <string>
#include "commands.h"

namespace potapova
{
  template < typename Polygons >
  using CommandFunc = std::function< void(Polygons&, std::istream&, std::ostream&, std::ostream&) >;

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
