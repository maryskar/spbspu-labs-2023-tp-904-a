#include "helpFunctions.hpp"
#include <iostream>
#include <vector>
#include "Polygon.hpp"
#include "commandFunctions.hpp"
namespace malaya
{
  Commands::Commands()
  {
    dict1_.insert({"AREA EVEN", outAreaEven});
    dict1_.insert({"AREA ODD", outAreaOdd});
    dict1_.insert({"AREA MEAN", outAreaMean});
    dict1_.insert({"MIN AREA", outMinArea});
    dict1_.insert({"MIN VERTEXES", outMinVertexes});
    dict1_.insert({"MAX AREA", outMaxArea});
    dict1_.insert({"MAX VERTEXES", outMaxVertexes});
    dict1_.insert({"COUNT EVEN", outCountEven});
    dict1_.insert({"COUNT ODD", outCountOdd});
    dict1_.insert({"RECTS", outRects});
    dict2_.insert({"AREA", outAreaNum});
    dict2_.insert({"COUNT", outCountNum});
    dict3_.insert({"PERMS", outPerms});
  }
  void Commands::doComm(const std::string & comm, const std::vector< Polygon > & data, std::ostream & out) const
  {
    auto func = dict1_.at(comm);
    func(data, out);
  }
  void Commands::doComm(const std::string & comm, const std::vector< Polygon > & data,
                        size_t num, std::ostream & out) const
  {
    auto func = dict2_.at(comm);
    func(data, num, out);
  }
  void Commands::doComm(const std::string & comm, const std::vector< Polygon > & data,
                        std::ostream & out, std::istream & in) const
  {
    auto func = dict3_.at(comm);
    func(data, out, in);
  }

  std::string inputCommand(std::istream & in)
  {
    std::string command = " ";
    in >> command;
    if (!in)
    {
      throw std::runtime_error("file ends here");
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
  void doCommand(const std::vector< Polygon > & data, const Commands & dicts, std::string & command,
      std::istream & in, std::ostream & out)
  {
    try
    {
      dicts.doComm(command, data, out);
      return;
    }
    catch(const std::out_of_range & e)
    {}
    try
    {
      dicts.doComm(command, data, out, in);
      return;
    }
    catch(const std::out_of_range & e)
    {}
    size_t pos = command.find(' ');
    size_t num = std::stoull(command.substr(pos));
    dicts.doComm(command.substr(0, pos), data, num, out);
  }
}
