#include <iostream>
#include <iterator>
#include <fstream>
#include <deque>
#include <limits>
#include <exception>
#include <map>
#include <functional>
#include "polygon.h"
#include "outCommand.h"
int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Wrong number of parameters" << '\n';
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Could not open the file" << '\n';
    return 2;
  }
  std::deque< avdeeva::Polygon > polygons;
  using istreamIt = std::istream_iterator< avdeeva::Polygon >;
  while (!input.eof())
  {
    std::copy(istreamIt(input), istreamIt(), std::back_inserter(polygons));
    if (input.fail())
    {
      input.clear();
      auto maxstream = std::numeric_limits< std::streamsize >::max();
      input.ignore(maxstream, '\n');
    }
  }
  using cmd_t = std::function< void (const std::deque< avdeeva::Polygon > &, std::istream &, std::ostream &) >;
  std::map< std::string, cmd_t > commands;
  commands.insert({ "AREA", avdeeva::areaCommand });
  commands.insert({ "MAX", avdeeva::maxCommand });
  commands.insert({ "MIN", avdeeva::minCommand });
  commands.insert({ "COUNT", avdeeva::countCommand });
  commands.insert({ "RIGHTSHAPES", avdeeva::rightshapesCommand });
  commands.insert({ "INFRAME", avdeeva::inframeCommand });
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::string command;
    std::cin >> command;
    if (command.empty())
    {
      continue;
    }
    try
    {
      commands.at(command)(polygons, std::cin, std::cout);
    }
    catch (const std::exception & e)
    {
      std::cout << "<INVALID COMMAND>" << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
