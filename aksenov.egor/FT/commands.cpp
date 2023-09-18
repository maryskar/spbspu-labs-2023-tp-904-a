#include "commands.h"
#include <limits>
#include <stdexcept>
#include <algorithm>
#include "commandsImpl.h"

std::string insertCommand(std::istream &in)
{
  std::string command = "";
  in >> command;
  if (!in)
  {
    throw std::runtime_error("empty stream");
  }
  return command;
}

Commands::Commands()
{
  dict1_.insert({"CREATE", createDict});
  dict2_.insert({"OUT", outDictionaries});
  dict3_.insert({"TRANSLATE", translate});
  dict4_.insert({"HELP", help});
  dict3_.insert({"INTERSECTION", doIntersect});
  dict3_.insert({"UNITE", unite});
  dict4_.insert({"HISTORY", showHistory});
}

void Commands::doCommand(const std::string &command, std::istream &in, dictOfDicts &dict)
{
  auto func = dict1_.at(command);
  func(in, dict);
}
void Commands::doCommand(const std::string &command, const dictOfDicts &dict, std::ostream &out)
{
  auto func = dict2_.at(command);
  func(dict, out);
}
void Commands::doCommand(const std::string &command, std::istream &in, dictOfDicts &dict, std::ostream &out)
{
  auto func = dict3_.at(command);
  func(in, dict, out);
}
void Commands::doCommand(const std::string &command, std::ostream &out)
{
  auto func = dict4_.at(command);
  func(out);
}
void executeCommand(std::ostream &out, std::istream &in, Commands &commands, dictOfDicts &dict, std::string command)
{
  try
  {
    if (command == "CREATE")
    {
      commands.doCommand(command, in, dict);
    }
    else if (command == "OUT")
    {
      commands.doCommand(command, dict, out);
    }
    else if (command == "TRANSLATE")
    {
      commands.doCommand(command, in, dict, out);
    }
    else if (command == "HELP")
    {
      commands.doCommand(command, out);
    }
    else if (command == "INTERSECTION")
    {
      commands.doCommand(command, in, dict, out);
    }
    else if (command == "UNITE")
    {
      commands.doCommand(command, in, dict, out);
    }
    else if (command == "HISTORY")
    {
      commands.doCommand(command, out);
    }
    else
    {
      out << "invalid command" << "\n";
    }
  }
  catch (const std::out_of_range &e)
  {
    out << "command not found" << "\n";
  }
}
