#include "helpFunctions.hpp"
#include <iostream>
#include <vector>
#include "Polygon.hpp"
#include "commandFunctions.hpp"
namespace malaya
{
  Commands::Commands()
  {
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
    dict2.insert({"AREA", outAreaNum});
    dict2.insert({"COUNT", outCountNum});
    dict3.insert({"PERMS", outPerms});
  }
  void Commands::doComm(const std::string & comm, const std::vector< Polygon > & data, std::ostream & out) const
  {
    auto func = dict1.at(comm);
    func(data, out);
  }
  void Commands::doComm(const std::string & comm, const std::vector< Polygon > & data,
                        size_t num, std::ostream & out) const
  {
    auto func = dict2.at(comm);
    func(data, num, out);
  }
  void Commands::doComm(const std::string & comm, const std::vector< Polygon > & data,
                        std::ostream & out, std::istream & in) const
  {
    auto func = dict3.at(comm);
    func(data, out, in);
  }
  //const Commands::firstDict & Commands::getFirst() const
  //{
  //  return dict1;
  //}
  //const Commands::secondDict & Commands::getSecond() const
  //{
  //  return dict2;
  //}
  //const Commands::thirdDict & Commands::getThird() const
  //{
  //  return dict3;
  //}

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
    dicts.doComm(command, data, num, out);

    //auto iter1 = dicts.getFirst().find(command);
    //if (iter1 != dicts.getFirst().end())
    //{
    //  auto function = *iter1->second;
    //  function(data, out);
    //  return;
    //}
    //auto iter2 = dicts.getThird().find(command);
    //if (iter2 != dicts.getThird().end())
    //{
    //  auto function = *iter2->second;
    //  function(data, out, in);
    //  return;
    //}
    //size_t pos = command.find(' ');
    //auto iter3 = dicts.getSecond().find(command.substr(0, pos));
    //if (iter3 != dicts.getSecond().end())
    //{
    //  size_t num = std::stoull(command.substr(pos));
    //  auto function = *iter3->second;
    //  function(data, num, out);
    //  return;
    //}
    //if (!in.eof())
    //{
    //  invalidPrint(out);
    //  out << '\n';
    //  in.setstate(std::ios::failbit);
    //  return;
  }
}
