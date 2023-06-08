#include "command_dict.h"
#include "commands.h"
dimkashelk::comm_dict_t dimkashelk::createCommDict()
{
  dimkashelk::comm_dict_t res{};
  res.dic1["AREA EVEN"] = printAreaEven;
  res.dic1["AREA ODD"] = printAreaOdd;
  res.dic1["AREA MEAN"] = printAreaMean;
  res.dic2["AREA"] = printAreaNumOfVertex;
  res.dic1["MAX AREA"] = printMaxArea;
  res.dic1["MAX VERTEXES"] = printMaxVertex;
  res.dic1["MIN AREA"] = printMinArea;
  res.dic1["MIN VERTEXES"] = printMinVertex;
  res.dic1["COUNT EVEN"] = printCountEven;
  res.dic1["COUNT ODD"] = printCountOdd;
  res.dic2["COUNT"] = printCountNumOfVertex;
  res.dic3["INTERSECTIONS"] = printIntersections;
  res.dic3["SAME"] = printSame;
  return res;
}
