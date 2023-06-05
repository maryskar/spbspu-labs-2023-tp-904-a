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
    if (!in)
    {
      throw std::out_of_range("file ends here");
    }
    if (command != "RECTS" && command != "PERMS")
    {
      std::string param = " ";
      in >> param;
      if (!in)
      {
        throw std::invalid_argument("incorrect command parameter");
      }
      command = command + " " + param;
    }
    return command;
  }
  std::ostream & invalidPrint(std::ostream & out)
  {
    out << "<INVALID COMMAND>";
    return out;
  }
  void doCommand(const std::vector< Polygon > & data, const details::comms & dicts, std::string & command,
                 std::istream & in, std::ostream & out)
  {
    auto iter1 = std::get< 0 >(dicts).find(command);
    if (iter1 != std::get< 0 >(dicts).end())
    {
      auto function = *iter1->second;
      function(data, out);
      return;
    }
    auto iter2 = std::get< 2 >(dicts).find(command);
    if (iter2 != std::get< 2 >(dicts).end())
    {
      auto function = *iter2->second;
      function(data, out, in);
      return;
    }
    size_t pos = command.find(' ');
    auto iter3 = std::get< 1 >(dicts).find(command.substr(0, pos));
    if (iter3 != std::get< 1 >(dicts).end())
    {
      size_t num = stoull(command.substr(pos));
      auto function = *iter3->second;
      function(data, num, out);
      return;
    }
    if (!in.eof())
    {
      invalidPrint(out);
      out << '\n';
      in.setstate(std::ios::failbit);
      return;
    }
  }
  details::comms makeDictionary()
  {
    details::firstDict dict1;
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
    details::secondDict dict2;
    dict2.insert({"AREA", outAreaNum});
    dict2.insert({"COUNT", outCountNum});
    details::thirdDict dict3;
    dict3.insert({"PERMS", outPerms});
    return details::comms{dict1, dict2, dict3};
  }
}
