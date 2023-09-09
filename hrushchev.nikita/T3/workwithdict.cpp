#include "workwithdict.hpp"
#include <map>
#include <iostream>
#include "command.hpp"
#include "polygon.hpp"

hrushchev::Commands::Commands()
{
  dict1_.insert({"AREA EVEN", getAreaEven});
  dict1_.insert({"AREA ODD", getAreaOdd});
  dict1_.insert({"AREA MEAN", getAreaMean});
  dict2_.insert({"AREA", getAreaVertexes});
  dict1_.insert({"MAX AREA", getMaxArea});
  dict1_.insert({"MAX VERTEXES", getMaxVertexes});
  dict1_.insert({"MIN AREA", getMinArea});
  dict1_.insert({"MIN VERTEXES", getMinVertexes});
  dict1_.insert({"COUNT EVEN", getCountEven});
  dict1_.insert({"COUNT ODD", getCountOdd});
  dict2_.insert({"COUNT", getCountVertexes});
  dict3_.insert({"RMECHO", rmEcho});
  dict3_.insert({"SAME", getSame});
}