#ifndef WORKWITHDICT_HPP
#define WORKWITHDICT_HPP

#include <string>
#include <queue>
#include <map>
#include "commands.hpp"

namespace hrushchev
{
  class Commands
  {
    public:
      Commands();
      void runCommand(std::istream& in, std::ostream& out);
    private:
      using com1 = void(*)(infix_dict&, str&, str&);
      using com2 = void(*)(postfix_dict&, infix_dict&, variables_dict&, str&, str&, int);
      using com3 = void(*)(postfix_dict&, str&, str&, str&, int);
      using com4 = void(*)(infix_dict&, std::ostream&);
      using com5 = void(*)(postfix_dict&, std::ostream&);
      using com6 = void(*)(std::ostream&);
      using com7 = void(*)(postfix_dict&, str&, std::ostream&);
      using com8 = void(*)(variables_dict&, str&, str&);
      using com9 = void(*)(variables_dict&, str&, std::ostream&);
      using com10 = void(*)(variables_dict&, std::ostream&);

      std::map< std::string, com1 > dict1_;
      std::map< std::string, com2 > dict2_;
      std::map< std::string, com3 > dict3_;
      std::map< std::string, com4 > dict4_;
      std::map< std::string, com5 > dict5_;
      std::map< std::string, com6 > dict6_;
      std::map< std::string, com7 > dict7_;
      std::map< std::string, com8 > dict8_;
      std::map< std::string, com9 > dict9_;
      std::map< std::string, com10 > dict10_;
  };
}

#endif

