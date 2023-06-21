#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include <fstream>
#include <string>
#include "polygon.h"
#include "commands.h"

int main(int argc, char** argv)
{
  if (argc > 2)
  {
    std::cerr << "Error\n";
    return 1;
  }
  std::ifstream inpFile;
  if (argc == 2)
  {
    inpFile.open(argv[1]);
    if (!inpFile.is_open())
    {
      std::cerr << "File isn't open\n";
      return 1;
    }
  }
  std::vector< mashkin::Polygon > res;
  using inpIter = std::istream_iterator< mashkin::Polygon >;
  constexpr auto maxSize = std::numeric_limits< std::streamsize >::max();
  while (!inpFile.eof())
  {
    std::copy(inpIter(inpFile), inpIter(), std::back_inserter(res));
    if (inpFile.fail())
    {
      inpFile.clear();
      inpFile.ignore(maxSize, '\n');
    }
  }
  while (!std::cin.eof())
  {
    std::string command;
    runCommand(std::cin, command, res);
  }
  return 0;
}
