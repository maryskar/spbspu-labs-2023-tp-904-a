#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <functional>
#include <message.h>
#include "funcs_for_commands.h"

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
     type_2(),
     type_3(),
     type_4()
   {
     names = {
       {"AREA"},
       {"COUNT"},
       {"AREA EVEN", "AREA ODD", "AREA MEAN", "MAX AREA", "MIN AREA"},
       {"MAX VERTEXES", "MIN VERTEXES", "COUNT EVEN", "COUNT ODD", "RIGHTSHAPES"},
       {"INFRAME"}
     };

     type_1.insert(std::make_pair("AREA", &getAreaWithEqualNumVerts));
     type_2.insert(std::make_pair("COUNT", &getNumWithEqualNumVerts));

     type_3.insert(std::make_pair("AREA EVEN", &getAreaEven));
     type_3.insert(std::make_pair("AREA ODD", &getAreaOdd));
     type_3.insert(std::make_pair("AREA MEAN", &getAreaMean));
     type_3.insert(std::make_pair("MAX AREA", &getMaxArea));
     type_3.insert(std::make_pair("MIN AREA", &getMinArea));

     type_4.insert(std::make_pair("MAX VERTEXES", &getMaxVerts));
     type_4.insert(std::make_pair("MIN VERTEXES", &getMinVerts));
     type_4.insert(std::make_pair("COUNT EVEN", &getNumEven));
     type_4.insert(std::make_pair("COUNT ODD", &getNumOdd));
     type_4.insert(std::make_pair("RIGHTSHAPES", &getNumRightShapes));

     type_5.insert(std::make_pair("INFRAME", &isInFrame));
   }

   void call(const std::string& command1, std::vector< Polygon >& data, std::istream& in, std::ostream& out)
   {
     try
     {
       if (findIn(command1, 4))
       {
         out << type_4.at(command1)(data) << "\n";
       }
       else if (findIn(command1, 5))
       {
         Polygon polygon;
         getFrameRect(in, polygon);
         out << (type_5.at(command1)(data, polygon) ? "<TRUE>" : "<FALSE>") << "\n";
       }
       else
       {
         std::string command2 = " ";
         in >> command2;

         if (!isdigit(command2[0]))
         {
           if (findIn(command1 + " " + command2, 3))
           {
             out << std::fixed << std::setprecision(1) << type_3.at(command1 + " " + command2)(data) << "\n";
           }
           else
           {
             out << type_4.at(command1 + " " + command2)(data) << "\n";
           }
         }
         else
         {
           auto n = std::stoull(command2);
           if (findIn(command1, 1))
           {
             out << std::fixed << std::setprecision(1) << type_1.at(command1)(data, n) << "\n";
           }
           else
           {
             out << type_2.at(command1)(data, n) << "\n";
           }
         }
       }
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
     auto in_any_of = [&](const auto& in_vector)
     {
       return std::any_of(in_vector.begin(), in_vector.end(), cond);
     };
     return std::any_of(names.begin(), names.end(), in_any_of);
   }

  private:
   std::vector< std::vector< std::string > > names;
   std::map< std::string, std::function< double(const std::vector< Polygon >&, const size_t&) > > type_1;
   std::map< std::string, std::function< size_t(const std::vector< Polygon >&, const size_t&) > > type_2;
   std::map< std::string, std::function< double(const std::vector< Polygon >&) > > type_3;
   std::map< std::string, std::function< size_t(const std::vector< Polygon >&) > > type_4;
   std::map< std::string, std::function< bool(const std::vector< Polygon >&, const Polygon&) > > type_5;
   bool findIn(const std::string& name, size_t type);
  };

  bool tarasenko::Commands::findIn(const std::string& name, size_t type)
  {
    size_t i = type - 1;
    return std::find(names[i].begin(), names[i].end(), name) != names[i].end();
  }
}
#endif
