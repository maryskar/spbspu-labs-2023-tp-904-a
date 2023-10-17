#include <iostream>
#include <fstream>
#include <deque>
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
    std::deque< Polygon > polygons = readPolygons(input_file);
    std::string command_name;
    std::unordered_map< std::string, CommandFunc< const std::deque< Polygon > > > non_changing_commands = getNonChangingCommands();
    std::unordered_map< std::string, CommandFunc< std::deque< Polygon > > > changing_commands = getChangingCommands();
    while (std::cin >> command_name)
    {
      std::unordered_map< std::string, CommandFunc< std::deque< Polygon > > >::const_iterator changing_command_ptr;
      if ((changing_command_ptr = changing_commands.find(command_name)) != changing_commands.cend())
      {
        changing_command_ptr->second(polygons, std::cin, std::cout, std::cerr);
        continue;
      }
      std::unordered_map< std::string, CommandFunc< const std::deque< Polygon > > >::const_iterator non_changing_command_ptr;
      if ((non_changing_command_ptr = non_changing_commands.find(command_name)) != non_changing_commands.cend())
      {
        non_changing_command_ptr->second(polygons, std::cin, std::cout, std::cerr);
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Memory allocation failed";
    return 1;
  }
  return 0;
}
