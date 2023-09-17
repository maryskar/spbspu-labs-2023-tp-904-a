#include <iostream>
#include <fstream>
#include "data_struct.h"
#include "read_polygons.h"
#include "commands.h"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cout << "Incorrect input\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cout << "File not found\n";
    return 1;
  }
  std::deque< tarasenko::Polygon > polygons = tarasenko::readPolygons(input);
  tarasenko::Commands commands;
  std::string name_of_command = " ";
  while (std::cin >> name_of_command)
  {
    try
    {
      commands.call(name_of_command, polygons, std::cin, std::cout);
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << "\n";
      return 1;
    }
  }
}
