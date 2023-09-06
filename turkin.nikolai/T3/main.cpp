#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>

#include "commands-list.hpp"
#include <out-msg.hpp>

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

  std::deque< turkin::Polygon > data;

  while (!file.eof())
  {
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      continue;
    }
    std::copy(std::istream_iterator< turkin::Polygon >(file), std::istream_iterator< turkin::Polygon >(), std::back_inserter(data));
  }

  while (std::cin)
  {
    std::string cmd;
    std::cin >> cmd;
    if (!std::cin)
    {
      break;
    }
    try
    {
      turkin::main_list.at(cmd)(data, std::cin, std::cout) << "\n";
    }
    catch (...)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      turkin::outInvalidCMD(std::cout);
    }
  }
}
