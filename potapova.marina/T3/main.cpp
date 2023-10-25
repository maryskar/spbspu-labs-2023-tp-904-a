#include <iostream>
#include <fstream>
#include <deque>
#include "workWithIO.h"
#include "readPolygons.h"
#include "commandsMap.h"

int main(int argc, char* argv[])
{
  using namespace potapova;
  if (argc != 2)
  {
    std::cerr << "Incorrect number of arguments\n";
    return 1;
  }
  std::ifstream input_file(argv[1]);
  if (!input_file.is_open())
  {
    std::cerr << "Failed to open file\n";
    return 1;
  }
  try
  {
    std::deque< Polygon > polygons;
    polygons = readPolygons(input_file);
    std::string command_name;
    NotChangingCommandsMap non_changing_commands = getNonChangingCommands();
    ChangingCommandsMap changing_commands = getChangingCommands();
    while (std::cin >> command_name)
    {
      ChangingCommandsMap::const_iterator changing_command_ptr;
      try
      {
        if ((changing_command_ptr = changing_commands.find(command_name)) != changing_commands.cend())
        {
          changing_command_ptr->second(polygons, std::cin, std::cout);
          continue;
        }
        NotChangingCommandsMap::const_iterator non_changing_command_ptr;
        if ((non_changing_command_ptr = non_changing_commands.find(command_name)) != non_changing_commands.cend())
        {
          non_changing_command_ptr->second(polygons, std::cin, std::cout);
        }
        else
        {
          throw std::logic_error("There are no commands");
        }
      }
      catch (const std::logic_error&)
      {
        handleInvalidCommand(std::cin, std::cout);
      }
    }
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Memory allocation failed\n";
    return 1;
  }
  return 0;
}
