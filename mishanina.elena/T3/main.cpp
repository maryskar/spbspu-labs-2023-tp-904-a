#include <iostream>
#include <fstream>
#include <limits>
#include "CommandsDictionary.h"
int main(int argc, char* argv[])
{
  using namespace mishanina;
  if (argc != 2){
    std::cerr << "Error : not enough CL parameters\n";
    return 1;
  }

  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Error : file not open" << '\n';
    return 1;
  }
  std::vector< Polygon > polygons;
  while (!input.eof())
  {
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(std::istream_iterator< Polygon >(input),
              std::istream_iterator< Polygon >(),
              std::back_inserter(polygons));
  }
  input.close();
  CommandDictionary dictionary;
  while (!std::cin.eof())
  {
    if(!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    try
    {
      std::string cmd = dictionary.readCommand(std::cin);
      dictionary.doCommand(polygons, cmd, std::cin, std::cout);
    }
    catch (const std::logic_error &e)
    {
      std::cout << "<INVALID COMMAND>\n";
      long long maxstream = std::numeric_limits< std::streamsize >::max();
      std::cin.ignore(maxstream, '\n');
      std::cin.clear();
    }
    catch (const std::runtime_error &e)
    {
      break;
    }
  }
  return 0;
}
