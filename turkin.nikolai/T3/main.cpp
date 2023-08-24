#include <fstream>
#include <iostream>
#include <iterator>

#include "commands-list.hpp"

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "no file\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "cannot open file\n";
    return 1;
  }

  std::vector< turkin::Polygon > data;
  std::copy(std::istream_iterator< turkin::Polygon >(file), std::istream_iterator< turkin::Polygon >(), std::back_inserter(data));

  while (std::cin)
  {
    std::string cmd;
    std::cin >> cmd;
    if (!std::cin)
    {
      break;
    }
    turkin::main_list[cmd](data, std::cin, std::cout) << "\n";
  }
}
