#include "helpFunctions.hpp"
#include <iostream>
#include <vector>
#include "Polygon.hpp"
#include "commandFunctions.hpp"

namespace malaya
{
  std::string inputCommand(std::istream & in)
  {
    std::string command = " ";
    in >> command;
    return command;
  }
  void invalidPrint(std::ostream & out)
  {
    out << "<INVALID COMMAND>" << '\n';
  }
  std::tuple< firstDict , secondDict , thirdDict > makeDictionary()
  {
    firstDict dict1;
    dict1.insert({"AREA EVEN", outAreaEven});
    dict1.insert({"AREA ODD", outAreaOdd});
    dict1.insert({"AREA MEAN", outAreaMean});
    dict1.insert({"MIN AREA", outMinArea});
    dict1.insert({"MIN VERTEXES", outMinVertexes});
    dict1.insert({"MAX AREA", outMaxArea});
    dict1.insert({"MAX VERTEXES", outMaxVertexes});
    dict1.insert({"COUNT EVEN", outCountEven});
    dict1.insert({"COUNT ODD", outCountOdd});
    dict1.insert({"RECTS", outRects});
    secondDict dict2;
    dict2.insert({"AREA VERTNUM", outAreaNum});
    dict2.insert({"COUNT VERTNUM", outCountNum});
    thirdDict dict3;
    dict3.insert({"PERMS", outPerms});
    return std::tuple< firstDict , secondDict , thirdDict > {dict1, dict2, dict3};

  }








  void doCommand(const std::vector< Polygon > & data, std::string & command, std::istream & in,
                 std::ostream & out)
  {
    //if(command == "AREA")
    //{
    //  std::string option = " ";
    //  in >> option;
    //  if(option == "EVEN")
    //  {
    //    outAreaEven(data, out);
    //  }
    //  else if(option == "ODD")
    //  {
    //    outAreaOdd(data, out);
    //  }
    //  else if(option == "MEAN")
    //  {
    //    outAreaMean(data, out);
    //  }
    //  else
    //  {
    //    unsigned long long number = std::stoull(option);
    //    if(number < 3)
    //    {
    //      invalidPrint(out);
    //    }
    //    else
    //    {
    //      outAreaNum(data, number, out);
    //    }
    //  }
    //}
    //else if(command == "MAX")
    //{
    //  std::string option = " ";
    //  in >> option;
    //  if(option == "AREA")
    //  {
    //    outMaxArea(data, out);
    //  }
    //  else if(option == "AREA")
    //  {
    //    outMaxVertexes(data, out);
    //  }
    //  else
    //  {
    //    invalidPrint(out);
    //  }
    //}
    //else if(command == "MIN")
    //{
    //  std::string option = " ";
    //  in >> option;
    //  if(option == "AREA")
    //  {
    //    outMinArea(data, out);
    //  }
    //  else if(option == "AREA")
    //  {
    //    outMinVertexes(data, out);
    //  }
    //  else
    //  {
    //    invalidPrint(out);
    //  }
    //}
    //else if(command == "COUNT")
    //{
    //  std::string option = " ";
    //  in >> option;
    //  if(option == "EVEN")
    //  {
    //    outCountEven(data, out);
    //  }
    //  else if(option == "ODD")
    //  {
    //    outCountOdd(data, out);
    //  }
    //  else
    //  {
    //    unsigned long long number = std::stoull(option);
    //    if(number < 3)
    //    {
    //      invalidPrint(out);
    //    }
    //    else
    //    {
    //      outCountNum(data, number, out);
    //    }
    //  }
    //}
    //else if(command == "PERMS")
    //{
    //  Polygon polygon;
    //  in >> polygon;
    //  if(!in)
    //  {
    //    invalidPrint(out);
    //    return;
    //  }
    //  outPerms(data, out, polygon);
    //}
    //else if(command == "RECTS")
    //{
    //  outRects(data, out);
    //}
    //else
    //{
    //  invalidPrint(out);
    //  in.setstate(std::ios::failbit);
    //}
  }
}