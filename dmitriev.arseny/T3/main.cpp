#include <iostream>
#include <fstream>
#include <numeric>
#include <limits>
#include <iterator>
#include "dictionary.h"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "invalid quantity of arguments" << '\n';
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "problems while opening file" << '\n';
    return 1;
  }

  std::vector< dmitriev::Polygon > polygons;
  auto maxNum = std::numeric_limits< std::streamsize >::max();

  while (!file.eof())
  {
    std::copy(std::istream_iterator< dmitriev::Polygon >(file),
      std::istream_iterator< dmitriev::Polygon >(),
      std::back_inserter(polygons));
    if (file.fail())
    {
      file.clear();
      file.ignore(maxNum, '\n');
    }
  }
  dmitriev::CommandsDictionaty cmd;
  while (!std::cin.eof())
  {
    try
    {
      dmitriev::runCommand(polygons, cmd, std::cout, std::cin);
    }
    catch (const std::logic_error&)
    {
      dmitriev::printInvalidCommand(std::cout);
      std::cout << '\n';
      if (!std::cin)
      {
        std::cin.clear();
      }
      std::cin.ignore(maxNum, '\n');
    }
    catch (const std::exception&)
    {
      break;
    }
  }

  return 0;
}
