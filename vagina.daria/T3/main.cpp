#include <iostream>
#include <iterator>
#include <fstream>
#include <functional>
#include <limits>
#include "commands.h"
#include "polygon.h"

int main(int argNum, char* argv[])
{
  if (argNum != 2)
  {
    std::cerr << "Error: wrong parameters number." << '\n';
    return 1;
  }
  std::cout << std::fixed;
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "Error: file could not be opened." << '\n';
    return 1;
  }
  /*constexpr auto max_size = std::numeric_limits< std::streamsize >::max();
  std::vector< vagina::Polygon > polygon;
  using istream_it = std::istream_iterator< vagina::Polygon >;
  while (!in.eof())
  {
    if (in.fail())
    {
      in.clear();
      in.ignore(max_size, '\n');
    }
    std::copy(istream_it(in), istream_it(), std::back_inserter(polygon));
  }
  in.close();
  auto dictionary = vagina::DictionaryOfCommands();
  while (!std::cin.eof())
  {
    try
    {
      auto read = vagina::readCommand(std::cin);
      vagina::doCommand(read, dictionary, polygon, std::cin, std::cout);
    }
    catch (const std::logic_error & e)
    {
      vagina::messageInvalidCommand(std::cout);
      std::cin.ignore(max_size, '\n');
    }
    catch (const std::runtime_error & e)
    {
      break;
    }
    if(!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }*/
  using inIter = std::istream_iterator< vagina::Polygon >;
  std::vector< vagina::Polygon > data;
  while (!in.eof())
  {
    std::copy(inIter(in), inIter(), std::back_inserter(data));
    if (!in)
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  vagina::DictionaryOfCommands comms;
  while (!std::cin.eof())
  {
    try
    {
      std::string command;
      command = vagina::readCommand(std::cin);
      vagina::doCommand(command, comms, data, std::cin, std::cout);
    }
    catch (const std::runtime_error &)
    {
      break;
    }
    catch (const std::logic_error &)
    {
      vagina::messageInvalidCommand(std::cout);
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
