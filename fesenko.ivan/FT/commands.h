#ifndef COMMANDS_H
#define COMMANDS_H
#include <iostream>
#include <unordered_map>
#include <forward_list>
#include <functional>
namespace fesenko
{
  class Commands
  {
   public:
    using hash_t = std::unordered_map< std::string, std::forward_list< size_t > >;
    using data_t = std::unordered_map< std::string, hash_t >;
    Commands();
    void make(const std::string &command, const std::string dict_name, std::istream &in, std::ostream &out);
   private:
    using commands1 = std::function< void(const data_t data, std::istream &in) >;
    using commands2 = std::function< void(const data_t data, std::istream &in, std::ostream &out) >;
    std::unordered_map< std::string, commands1 > type1;
    std::unordered_map< std::string, commands2 > type2;
  };
}
#endif
