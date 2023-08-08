#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <limits>
#include "Polygon.hpp"
#include "helpFunctions.hpp"
int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Not enough args\n";
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "File not found\n";
    return 2;
  }
  using inIter = std::istream_iterator< malaya::Polygon >;
  std::vector< malaya::Polygon > data;
  while (!in.eof())
  {
    std::copy(inIter(in), inIter(), std::back_inserter(data));
    if (!in)
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  malaya::Commands comms;
  while (!std::cin.eof())
  {
    try
    {
      std::string command;
      command = malaya::inputCommand(std::cin);
      malaya::doCommand(data, comms, command, std::cin, std::cout);
    }
    catch (const std::runtime_error &)
    {
      break;
    }
    catch (const std::logic_error &)
    {
      malaya::invalidPrint(std::cout);
      std::cout << '\n';
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    if(!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
