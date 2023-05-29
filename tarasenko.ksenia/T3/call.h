#ifndef CALL_H
#define CALL_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <iomanip>
#include "commands.h"
#include "message.h"

namespace tarasenko
{
  void call(const std::string& command, std::vector< Polygon >& p, std::istream& in, std::ostream& out)
  {
    Commands commands;
    if (command == "AREA")
    {
      std::string name_of_command = "";
      in >> name_of_command;
      auto command = commands.calc(name_of_command);
      out << std::fixed << std::setprecision(1) << command(p) << "\n";
    }
    else
    {
      out << outMessageInvalidCommand << "\n";
      std::string trash = "";
      getline(in, trash);
    }
  }
}
#endif
