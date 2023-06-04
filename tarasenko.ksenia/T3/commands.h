#ifndef COMMANDS_H
#define COMMANDS_H

#include <map>
#include <functional>
#include "data_struct.h"
#include "funcs_for_commands.h"

namespace tarasenko
{
  class Commands
  {
  public:
   Commands():
     names(),
     type_1(),
     type_2()
   {
     names = {"AREA", "MAX", "MIN", "COUNT", "INFRAME", "RIGHTSHAPES"};

     type_1.insert(std::make_pair("AREA", &getAreaWithEqualNumVerts));
     //type_1.insert(std::make_pair("COUNT", &getAreaWithEqualNumVerts));

     type_2.insert(std::make_pair("AREA EVEN", &getAreaEven));
     type_2.insert(std::make_pair("AREA ODD", &getAreaOdd));
     type_2.insert(std::make_pair("AREA MEAN", &getAreaMean));
     type_2.insert(std::make_pair("MAX AREA", &getMaxArea));
     type_2.insert(std::make_pair("MIN AREA", &getMinArea));
     type_2.insert(std::make_pair("MAX VERTEXES", &getMaxVerts));
     type_2.insert(std::make_pair("MIN VERTEXES", &getMinVerts));
   }

   bool find(const std::string& name)
   {
     return std::find(names.begin(), names.end(), name) != names.end();
   }

   void get(const std::string& key, std::function< double(const std::vector< Polygon >&, const size_t&) >& command)
   {
     try
     {
       command = type_1.at(key);
     }
     catch (const std::out_of_range&)
     {
       throw std::out_of_range("Not found");
     }
   }

   void get(const std::string& key, std::function< double(const std::vector< Polygon >&) >& command)
   {
     try
     {
       command = type_2.at(key);
     }
     catch (const std::out_of_range&)
     {
       throw std::out_of_range("Not found");
     }
   }

  private:
   std::vector< std::string > names;
   std::map< std::string, std::function< double(const std::vector< Polygon >&, const size_t&) > > type_1;
   std::map< std::string, std::function< double(const std::vector< Polygon >&) > > type_2;
  };
}
#endif
