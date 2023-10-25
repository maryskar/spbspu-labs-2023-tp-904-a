#ifndef COMMANDS_H
#define COMMADNS_H
#include <iostream>
#include <deque>
#include <functional>
#include <map>
#include "polygon.h"
namespace fesenko
{
  class Commands
  {
   public:
    using data_t = std::deque< Polygon >;
    Commands();
    void make(const std::string &command1, data_t &data, std::istream &in, std::ostream &out);
   private:
    using commands1 = std::function< std::ostream &(const data_t &, size_t, std::ostream &) >;
    using commands2 = std::function< std::ostream &(const data_t &, std::ostream &) >;
    using commands3 = std::function< std::ostream &(const data_t &, std::istream &, std::ostream &) >;
    std::map< std::string, commands1 > type1;
    std::map< std::string, commands2 > type2;
    std::map< std::string, commands3 > type3;
  };
}
#endif
