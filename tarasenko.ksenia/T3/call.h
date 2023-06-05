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
  std::istream& readTrash(std::istream& in)
  {
    std::string trash = "";
    std::getline(in, trash);
    return in;
  }

  void call(const std::string& command1, std::vector< Polygon >& p, std::istream& in, std::ostream& out)
  {
    Commands commands;
    std::string command2 = "";
    in >> command2;
    try
    {
      if (!isdigit(command2[0]))
      {
        if (commands.findIn(command1 + " " + command2, 3))
        {
          std::function< double(const std::vector< Polygon >&) > command;
          commands.get(command1 + " " + command2, command);
          out << std::fixed << std::setprecision(1) << command(p) << "\n";
        }
        else
        {
          std::function< size_t(const std::vector< Polygon >&) > command;
          commands.get(command1 + " " + command2, command);
          out << command(p) << "\n";
        }
      }
      else
      {
        if (commands.findIn(command1, 1))
        {
          std::function< double(const std::vector< Polygon >&, const size_t&) > command;
          commands.get(command1, command);
          auto n = std::stoull(command2);
          out << std::fixed << std::setprecision(1) << command(p, n) << "\n";
        }
        else
        {
          std::function< size_t(const std::vector< Polygon >&, const size_t&) > command;
          commands.get(command1, command);
          auto n = std::stoull(command2);
          out << command(p, n) << "\n";
        }
      }
    }
    catch (const std::exception&)
    {
      out << outMessageInvalidCommand << "\n";
      readTrash(in);
    }
  }
}
#endif
