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
  long long maxstream = std::numeric_limits< std::streamsize >::max();
  std::vector< Polygon > pols;
  while (!input.eof())
  {
    if (input.fail())
    {
      input.clear();
      input.ignore(maxstream, '\n');
    }
    std::copy(std::istream_iterator< Polygon >(input), std::istream_iterator< Polygon >(), std::back_inserter(pols));
  }
  input.close();
  CommandDictionary dictionary;
  while (!std::cin.eof())
  {
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(maxstream, '\n');
    }
    try
    {
      std::string cmd = dictionary.readCommand(std::cin);
      dictionary.doCommand(pols, cmd, std::cin, std::cout);
    }
    catch (const std::logic_error &e)
    {
      std::cout << "<INVALID COMMAND>\n";
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
