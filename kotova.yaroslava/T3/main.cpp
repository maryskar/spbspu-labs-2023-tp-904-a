#include <iostream>
#include <iterator>
#include <fstream>
#include <functional>
#include <limits>
#include "geomfigures.hpp"
#include "outMessages.hpp"
int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Error." << '\n';
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Error." << '\n';
    return 1;
  }
  std::vector< kotova::Polygon > polygons;
  while (!input.eof())
  {
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(std::istream_iterator< kotova::Polygon >(input), std::istream_iterator< kotova::Polygon >(), std::back_inserter(polygons));
  }
  input.close();
  auto dict = kotova::CommandDictionary();
  while (!std::cin.eof())
  {
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    try
    {
      auto read = dict.readCommand(std::cin);
      dict.doCommand(read, polygons, dict, std::cin, std::cout);
    }
    catch (const std::logic_error &e)
    {
      kotova::outMessageError(std::cout);
      std::cout << '\n';
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cin.clear();
    }
    catch (const std::runtime_error &e)
    {
      break;
    }
  }
  return 0;
}
