#include "commands.h"
#include <iostream>
#include <algorithm>

void runRightshapes(std::istream& inp, std::string& command);
void runPerms(std::istream& inp, std::string& command);
void runCount(std::istream& inp, std::string& command);
void runMin(std::istream& inp, std::string& command);
void runMax(std::istream& inp, std::string& command);
void runArea(std::istream& inp, std::string& command);

void runArea(std::istream& inp, std::string& command)
{

}

void runCommand(std::istream& inp, std::string& command)
{
  inp >> command;
  if (command == "AREA")
  {
    runArea(inp, command);
  }
  else if (command == "MAX")
  {
    runMax(inp, command);
  }
  else if (command == "MIN")
  {
    runMin(inp, command);
  }
  else if (command == "COUNT")
  {
    runCount(inp, command);
  }
  else if (command == "PERMS")
  {
    runPerms(inp, command);
  }
  else if (command == "RIGHTSHAPES")
  {
    runRightshapes(inp, command);
  }
}
