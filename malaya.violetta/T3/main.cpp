#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <limits>
#include "Polygon.hpp"
#include "helpFunctions.hpp"

int main(int argc, char * argv[]) //?????
{
  //std::string filename;
  //std::cin >> filename;
  if(argc != 2)
  {
    std::cerr << "Not enough args\n";
    return -1;
  }
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "File not found\n";
    return -2;
  }
  using inIter = std::istream_iterator< malaya::Polygon >;
  std::vector< malaya::Polygon > data;
  std::copy(inIter(in), inIter(), std::back_inserter(data));
  auto comms = malaya::makeDictionary();
  while (!std::cin.eof())
  {
    std::string command = malaya::inputCommand(std::cin);
    try
    {
      malaya::doCommand(data, comms, command, std::cin, std::cout);
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
