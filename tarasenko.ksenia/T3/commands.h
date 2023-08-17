#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <message.h>
#include "funcs_for_map_commands.h"

namespace tarasenko
{
  using namespace std::placeholders;

  std::istream& readTrash(std::istream& in)
  {
    std::string trash = " ";
    std::getline(in, trash);
    return in;
  }

  class Commands
  {
  public:
   Commands():
     names(),
     cms()
   {
     names = {"AREA", "COUNT", "INFRAME", "AREA EVEN", "AREA ODD", "AREA MEAN", "MAX AREA", "MIN AREA",
        "MAX VERTEXES", "MIN VERTEXES", "COUNT EVEN", "COUNT ODD", "RIGHTSHAPES"};

     cms.insert(std::make_pair("AREA", &getAreaWithEqualNumVertsCommand));
     cms.insert(std::make_pair("COUNT", &getNumWithEqualNumVertsCommand));
     cms.insert(std::make_pair("AREA EVEN", &getAreaEvenCommand));
     cms.insert(std::make_pair("AREA ODD", &getAreaOddCommand));
     cms.insert(std::make_pair("AREA MEAN", &getAreaMeanCommand));
     cms.insert(std::make_pair("MAX AREA", &getMaxAreaCommand));
     cms.insert(std::make_pair("MIN AREA", &getMinAreaCommand));
     cms.insert(std::make_pair("MAX VERTEXES", &getMaxVertsCommand));
     cms.insert(std::make_pair("MIN VERTEXES", &getMinVertsCommand));
     cms.insert(std::make_pair("COUNT EVEN", &getNumEvenCommand));
     cms.insert(std::make_pair("COUNT ODD", &getNumOddCommand));
     cms.insert(std::make_pair("RIGHTSHAPES", &getNumRightShapesCommand));
     cms.insert(std::make_pair("INFRAME", &isInFrameCommand));
   }

   void call(const std::string& command1, std::vector< Polygon >& data, std::istream& in, std::ostream& out)
   {
     try
     {
       try
       {
         char c1;
         in.get(c1);
         if (c1 != ' ')
         {
           cms.at(command1)(data, in, out) << "\n";
           return;
         }
         else
         {
           char c2;
           in.get(c2);
           in.putback(c2);
           if (isdigit(c2))
           {
             cms.at(command1)(data, in, out) << "\n";
             return;
           }
         }
       }
       catch (...)
       {}
       std::string command2 = " ";
       in >> command2;
       cms.at(command1 + " " + command2)(data, in, out) << "\n";
     }
     catch (const std::exception&)
     {
       out << outMessageInvalidCommand << "\n";
       readTrash(in);
     }
   }

   bool find(const std::string& name)
   {
     auto cond = std::bind(std::equal_to< std::string >{}, _1, name);
     return std::any_of(names.begin(), names.end(), cond);
   }

  private:
   std::vector< std::string > names;
   using command_t = std::function< std::ostream&(const std::vector< Polygon >&, std::istream&, std::ostream&) >;
   std::map< std::string, command_t > cms;
  };
}
#endif
