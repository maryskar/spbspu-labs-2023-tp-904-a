#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <limits>
#include "Polygon.hpp"
#include "helpFunctions.hpp"

int main()
{
  std::string filename;
  std::cin >> filename;
  std::ifstream in (filename);
  using inIter = std::istream_iterator< malaya::Polygon >;
  std::vector< malaya::Polygon > data;
  std::copy(inIter(in), inIter(), std::back_inserter(data));
  std::string command;
  while(!std::cin.eof())
  {
    command = malaya::inputCommand(std::cin);
    try
    {
      malaya::doCommand(data, command, std::cin, std::cout);
    }
    catch(const std::invalid_argument & exception)
    {
      malaya::invalidPrint(std::cout);
    }

    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      continue;
    }
  }
  return 0;
}
