#include <iostream>
#include <iterator>
#include <fstream>
#include <functional>
#include <limits>
#include <commands.h>
#include <polygon.h>

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
  constexpr auto max_size = std::numeric_limits< std::streamsize >::max();
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
      auto read = dictionary.readCommand(std::cin);
      dictionary.doCommand(read, dictionary, polygon, std::cin, std::cout);
    }
    catch (const std::logic_error& e)
    {
      vagina::messageInvalidCommand(std::cout);
      std::cin.ignore(max_size, '\n');
    }
    catch (const std::runtime_error& e)
    {
        break;
    }
    if(!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
