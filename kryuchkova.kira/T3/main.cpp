#include <iostream>
#include <vector>
#include <limits>
#include <iterator>
#include <fstream>
#include "polygon.h"
#include "commands_dict.h"

std::string getCommand(std::istream & in)
{
  std::string res;
  in >> res;
  if (!in)
  {
    throw std::runtime_error("eof");
  }
  std::string name;
  in >> name;
  if (!in)
  {
    throw std::invalid_argument("Invalid command");
  }
  res += ' ' + name;
  return res;
}

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "File error\n";
    return 2;
  }
  constexpr auto max_size = std::numeric_limits< std::streamsize >::max();
  using input_iter = std::istream_iterator< kryuchkova::Polygon >;
  std::vector< kryuchkova::Polygon > pol;
  while (!in.eof())
  {
    std::copy(input_iter(in), input_iter(), std::back_inserter(pol));
    if (!in)
    {
      in.clear();
      in.ignore(max_size, '\n');
    }
  }
  kryuchkova::CommandDict commDict;
  while (!std::cin.eof())
  {
    try
    {
      auto comm = getCommand(std::cin);
      commDict.handleCommand(comm, pol, std::cout, std::cin);
      std::cout << '\n';
    }
    catch(const std::logic_error & e)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(max_size, '\n');
      std::cin.clear();
    }
    return 0;
  }
  
}
