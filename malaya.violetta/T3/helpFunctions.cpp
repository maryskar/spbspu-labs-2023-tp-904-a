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
    if (!(command == "RECTS" || command == "PERMS"))
    {
      std::string param = " ";
      in >> param;
      command = command + " " + param;
    }
    return command;
  }
  void invalidPrint(std::ostream & out)
  {
    out << "<INVALID COMMAND>\n";
  }
  void doCommand(const std::vector< Polygon > & data, const allComms & dicts, std::string & command, std::istream & in,
                 std::ostream & out)
  {
    auto iter1 = std::get< 0 >(dicts).find(command);
    bool com1 = false;
    bool com2 = false;
    bool com3 = false;
    if (iter1 != std::get< 0 >(dicts).end())
    {
      com1 = true;
      auto function = *iter1->second;
      function(data, out);
      return;
    }
    auto iter2 = std::get< 2 >(dicts).find(command);
    if (iter2 != std::get< 2 >(dicts).end())
    {
      com2 = true;
      auto function = *iter2->second;
      function(data, out, in);
      return;
    }
    size_t pos = command.find(' ');
    auto iter3 = std::get< 1 >(dicts).find(command.substr(0, pos));
    if (iter3 != std::get< 1 >(dicts).end())
    {
      com3 = true;
      size_t num = stoull(command.substr(pos));
      auto function = *iter3->second;
      function(data, num, out);
      return;
    }
    //if (!com1 && !com2 && !com3)
    //{
    //  invalidPrint(out);
    //}
    invalidPrint(out);
  }

  allComms makeDictionary()
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
    dict2.insert({"AREA", outAreaNum});
    dict2.insert({"COUNT", outCountNum});
    thirdDict dict3;
    dict3.insert({"PERMS", outPerms});
    return allComms{dict1, dict2, dict3};
  }
}
