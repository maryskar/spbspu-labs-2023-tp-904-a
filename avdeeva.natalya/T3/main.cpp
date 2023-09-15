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
    std::cerr << "Not enough CL parameters" << '\n';
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "File not open" << '\n';
    return 2;
  }
  std::deque< avdeeva::Polygon > polygons;
  while (!input.eof())
  {
    std::copy(std::istream_iterator< avdeeva::Polygon >(input),
      std::istream_iterator< avdeeva::Polygon >(),
      std::back_inserter(polygons));
    if (input.fail())
    {
      input.clear();
      auto maxstream = std::numeric_limits< std::streamsize >::max();
      input.ignore(maxstream, '\n');
    }
  }
  using cmd = std::function< void (const std::deque< avdeeva::Polygon > &,
    std::istream &, std::ostream &) >;
  std::map< std::string, cmd > commands(
    {
      {"AREA", avdeeva::areaCommand},
      {"MAX", avdeeva::maxCommand},
      {"MIN", avdeeva::minCommand},
      {"COUNT", avdeeva::countCommand},
      {"RIGHTSHAPES", avdeeva::rightshapesCommand},
      {"INFRAME", avdeeva::inframeCommand}
    });
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
