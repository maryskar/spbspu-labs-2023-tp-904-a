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
     type_1(),
     type_2()
   {
     names = {"AREA", "COUNT", "INFRAME", "AREA EVEN", "AREA ODD", "AREA MEAN", "MAX AREA", "MIN AREA",
        "MAX VERTEXES", "MIN VERTEXES", "COUNT EVEN", "COUNT ODD", "RIGHTSHAPES"};

     type_1.insert(std::make_pair("AREA", &getAreaWithEqualNumVertsCommand));
     type_1.insert(std::make_pair("COUNT", &getNumWithEqualNumVertsCommand));
     type_1.insert(std::make_pair("INFRAME", &isInFrameCommand));

     type_2.insert(std::make_pair("AREA EVEN", &getAreaEvenCommand));
     type_2.insert(std::make_pair("AREA ODD", &getAreaOddCommand));
     type_2.insert(std::make_pair("AREA MEAN", &getAreaMeanCommand));
     type_2.insert(std::make_pair("MAX AREA", &getMaxAreaCommand));
     type_2.insert(std::make_pair("MIN AREA", &getMinAreaCommand));
     type_2.insert(std::make_pair("MAX VERTEXES", &getMaxVertsCommand));
     type_2.insert(std::make_pair("MIN VERTEXES", &getMinVertsCommand));
     type_2.insert(std::make_pair("COUNT EVEN", &getNumEvenCommand));
     type_2.insert(std::make_pair("COUNT ODD", &getNumOddCommand));
     type_2.insert(std::make_pair("RIGHTSHAPES", &getNumRightShapesCommand));
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
           type_2.at(command1)(data, out) << "\n";
           return;
         }
         else
         {
           char c2;
           in.get(c2);
           in.putback(c2);
           if (isdigit(c2))
           {
             type_1.at(command1)(data, in, out) << "\n";
             return;
           }
         }
       }
       catch (...)
       {}
       std::string command2 = " ";
       in >> command2;
       type_2.at(command1 + " " + command2)(data, out) << "\n";
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
   using commands_1 = std::function< std::ostream&(const std::vector< Polygon >&, std::istream&, std::ostream&) >;
   using commands_2 = std::function< std::ostream&(const std::vector< Polygon >&, std::ostream&) >;
   std::map< std::string, commands_1 > type_1;
   std::map< std::string, commands_2 > type_2;
  };
}
#endif
