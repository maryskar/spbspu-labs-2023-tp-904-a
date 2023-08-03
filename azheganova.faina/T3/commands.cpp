#include "commands.h"

azheganova::Commands createCommands()
{
  azheganova::Commands res;
  res.dict_1.insert({ "AREA EVEN", azheganova::getAreaEven });
  res.dict_1.insert({ "AREA ODD", azheganova::getAreaOdd });
  res.dict_1.insert({ "AREA MEAN", azheganova::getAreaMean });
  res.dict_1.insert({ "MAX AREA", azheganova::getMaxArea });
  res.dict_1.insert({ "MAX VERTEXES", azheganova::getMaxVertexes });
  res.dict_1.insert({ "MIN AREA", azheganova::getMinArea });
  res.dict_1.insert({ "MIN VERTEXES", azheganova::getMinVertexes });
  res.dict_1.insert({ "COUNT EVEN", azheganova::countEven });
  res.dict_1.insert({ "COUNT ODD", azheganova::countOdd });
  res.dict_2.insert({ "AREA", azheganova::getAreaNumOfVertexes });
  res.dict_2.insert({ "COUNT", azheganova::countNumOfVertexes });
  res.dict_3.insert({ "RMECHO", azheganova::getRmecho });
  res.dict_3.insert({ "RIGHTSHAPES", azheganova::getRightshapes });
  return res;
}
