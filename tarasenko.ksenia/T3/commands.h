#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>
#include <map>
#include <deque>
#include <vector>
#include <functional>
#include "data_struct.h"

namespace tarasenko
{
  using namespace std::placeholders;

  class Commands
  {
  public:
   using data_t = std::deque< Polygon >;
   Commands();
   void call(const std::string& command1, data_t& data, std::istream& in, std::ostream& out);
   bool find(const std::string& name);

  private:
   std::vector< std::string > names;
   using commands_1 = std::function< std::ostream&(const data_t&, std::istream&, std::ostream&) >;
   using commands_2 = std::function< std::ostream&(const data_t&, std::ostream&) >;
   std::map< std::string, commands_1 > type_1;
   std::map< std::string, commands_2 > type_2;
  };
}
#endif
