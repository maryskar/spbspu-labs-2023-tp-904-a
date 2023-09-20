#include <iostream>
#include <sstream>
#include <limits>
#include "CommandsDictionary.h"
int main()
{
  using namespace mishanina;
  std::stringstream input{
    "3 (0;0) (1;1) (1;0)\n"
    "2 (0;0) (1;1)\n"
    "\n"
    "4 (0;0) (1;0) (1;1) (0;1)\n"
  };
  std::vector<Polygon> polygons;
  while (!input.eof())
  {
    std::copy(std::istream_iterator<Polygon>(input),
              std::istream_iterator<Polygon>(),
              std::back_inserter(polygons));
    if (input.fail())
    {
      input.clear();
      auto maxstream = std::numeric_limits<std::streamsize>::max();
      input.ignore(maxstream, '\n');
    }
  }
  CommandDictionary dictionary;
  while (!std::cin.eof())
  {
    try
    {
      std::string cmd = dictionary.readCommand(std::cin);
      dictionary.doCommand(polygons, cmd, dictionary, std::cin, std::cout);
    }
    catch (const std::logic_error &e)
    {
      std::cin.clear();
      long long maxstream = std::numeric_limits<std::streamsize>::max();
      std::cin.ignore(maxstream, '\n');
      std::cerr << "<INVALID COMMAND>\n";
    }
    catch (const std::runtime_error &e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }
  return 0;
}
