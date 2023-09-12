#ifndef COMMANDDICT_H
#define COMMANDDICT_H
#include <map>
#include <string>
#include "commands.h"

namespace azheganova
{
  class Commands
  {
  using command1_t = void(*)(std::vector< Polygon > & polygon, std::ostream & out);
  using command2_t = void(*)(std::vector< Polygon > & polygon, size_t n, std::ostream & out);
  using command3_t = void(*)(std::vector< Polygon > & polygon, std::ostream & out, std::istream &in);
  public:
    Commands();
    void doCommand(std::string command, std::vector< Polygon > & polygon, std::ostream & out, std::istream & in);
  private:
    std::map< std::string, command1_t > dict_1;
    std::map< std::string, command2_t > dict_2;
    std::map< std::string, command3_t > dict_3;
    std::map< std::string, command1_t > initializeDict1();
    std::map< std::string, command2_t > initializeDict2();
    std::map< std::string, command3_t > initializeDict3();
  };
}
#endif