#include <iostream>
#include <fstream>
#include <deque>
#include "dataStruct.h"
#include "readPolygons.h"
#include "commandsMap.h"

int main(int argc, char* argv[])
{
  using namespace potapova;
  std::ifstream input_file;
  if (argc != 2)
  {
    std::cerr << "Incorrect number of arguments\n";
    return 1;
  }
  else if (argc == 2)
  {
    input_file.open(argv[1]);
    if (!input_file.is_open())
    {
      std::cerr << "Failed to open file\n";
      return 1;
    }
  }
  else
  {
    std::cerr << "No file to open\n";
    return 1;
  }
  
  std::deque< Polygon > polygons = readPolygons(input_file);

  std::string command_name;
  std::unordered_map< std::string, CommandFunc< const std::deque< Polygon > > > non_changing_commands = getNonChangingCommands();
  std::unordered_map< std::string, CommandFunc< std::deque< Polygon > > > changing_commands = getChangingCommands();
  std::unordered_map< std::string, CommandFunc< std::deque< Polygon > > >::iterator command_ptr;
  while (std::cin >> command_name)
  {
    if (command_ptr = changing_commands.find(command_name) != changing_commands.end())
    {
      changing_commands[command_name](polygons, std::cin, std::cout, std::cerr);
    }
    else if (command_ptr = non_changing_commands.find(command_name) != non_changing_commands.end())
    {
      non_changing_commands[command_name](polygons, std::cin, std::cout, std::cerr);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
  return 0;
}