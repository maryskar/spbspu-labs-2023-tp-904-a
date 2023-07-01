#ifndef CALL_H
#define CALL_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <iomanip>
#include "commands.h"

namespace tarasenko
{
  std::ostream& outMessageInvalidCommand(std::ostream& out)
  {
    return out << "<INVALID COMMAND>";
  }

  std::istream& readTrash(std::istream& in)
  {
    std::string trash = "";
    std::getline(in, trash);
    return in;
  }

  void call(const std::string& command1, std::vector< Polygon >& data, std::istream& in, std::ostream& out)
  {
    Commands commands;
    try
    {
      if (commands.findIn(command1, 4))
      {
        std::function< size_t(const std::vector< Polygon >&) > command;
        commands.get(command1, command);
        out << command(data) << "\n";
      }
      else if (commands.findIn(command1, 5))
      {
        Polygon polygon;
        getFrameRect(in, polygon);
        std::function< bool(const std::vector< Polygon >&, const Polygon&) > command;
        commands.get(command1, command);
        out << (command(data, polygon) ? "<TRUE>" : "<FALSE>") << "\n";
      }
      else
      {
        std::string command2 = "";
        in >> command2;

        if (!isdigit(command2[0]))
        {
          if (commands.findIn(command1 + " " + command2, 3))
          {
            std::function< double(const std::vector< Polygon >&) > command;
            commands.get(command1 + " " + command2, command);
            out << std::fixed << std::setprecision(1) << command(data) << "\n";
          }
          else
          {
            std::function< size_t(const std::vector< Polygon >&) > command;
            commands.get(command1 + " " + command2, command);
            out << command(data) << "\n";
          }
        }
        else
        {
          if (commands.findIn(command1, 1))
          {
            std::function< double(const std::vector< Polygon >&, const size_t&) > command;
            commands.get(command1, command);
            auto n = std::stoull(command2);
            out << std::fixed << std::setprecision(1) << command(data, n) << "\n";
          }
          else
          {
            std::function< size_t(const std::vector< Polygon >&, const size_t&) > command;
            commands.get(command1, command);
            auto n = std::stoull(command2);
            out << command(data, n) << "\n";
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
}
#endif
