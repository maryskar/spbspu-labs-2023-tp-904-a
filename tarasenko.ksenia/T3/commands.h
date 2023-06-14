#ifndef COMMANDS_H
#define COMMANDS_H

#include <map>
#include <functional>
#include "data_struct.h"
#include "funcs_for_commands.h"

namespace tarasenko
{
  using namespace std::placeholders;

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

   bool find(const std::string& name)
   {
     auto cond = std::bind(std::equal_to< std::string >{}, _1, name);
     auto in_any_of = [&](const auto& in_vector) {
       return std::any_of(in_vector.begin(), in_vector.end(), cond);
     };
     return std::any_of(names.begin(), names.end(), in_any_of);
   }

   bool findIn(const std::string& name, size_t type)
   {
     size_t i = type - 1;
     return std::find(names[i].begin(), names[i].end(), name) != names[i].end();
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

   void get(const std::string& key, std::function< size_t(const std::vector< Polygon >&, const size_t&) >& command)
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

   void get(const std::string& key, std::function< double(const std::vector< Polygon >&) >& command)
   {
     try
     {
       command = type_3.at(key);
     }
     catch (const std::out_of_range&)
     {
       throw std::out_of_range("Not found");
     }
   }

   void get(const std::string& key, std::function< size_t(const std::vector< Polygon >&) >& command)
   {
     try
     {
       command = type_4.at(key);
     }
     catch (const std::out_of_range&)
     {
       throw std::out_of_range("Not found");
     }
   }

   void get(const std::string& key, std::function< bool(const std::vector< Polygon >&, const Polygon&) >& command)
   {
     try
     {
       command = type_5.at(key);
     }
     catch (const std::out_of_range&)
     {
       throw std::out_of_range("Not found");
     }
   }

  private:
   std::vector< std::vector< std::string > > names;
   std::map< std::string, std::function< double(const std::vector< Polygon >&, const size_t&) > > type_1;
   std::map< std::string, std::function< size_t(const std::vector< Polygon >&, const size_t&) > > type_2;
   std::map< std::string, std::function< double(const std::vector< Polygon >&) > > type_3;
   std::map< std::string, std::function< size_t(const std::vector< Polygon >&) > > type_4;
   std::map< std::string, std::function< bool(const std::vector< Polygon >&, const Polygon&) > > type_5;
  };
}
#endif
