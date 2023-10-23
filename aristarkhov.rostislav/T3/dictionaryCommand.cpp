#include "dictionaryCommand.h"

#include <iostream>
#include <iostruct.h>

#include "polygon.h"

aristarkhov::Commands::Commands()
{
  dict1.insert({ "AREA EVEN", areaEven });
  dict1.insert({ "AREA ODD", areaOdd });
  dict1.insert({ "AREA MEAN", areaMean });
  dict1.insert({ "MAX AREA", maxArea });
  dict1.insert({ "MAX VERTEXES", maxVertexes });
  dict1.insert({ "MIN AREA", minArea });
  dict1.insert({ "MIN VERTEXES", minVertexes });
  dict1.insert({ "COUNT EVEN", countEven });
  dict1.insert({ "COUNT ODD", countOdd });

  dict2.insert({ "AREA", areaVertexes });
  dict2.insert({ "COUNT", countVertexes });

  dict3.insert({ "RMECHO", rmEcho });
  dict3.insert({ "INFRAME", printInFrame });
}