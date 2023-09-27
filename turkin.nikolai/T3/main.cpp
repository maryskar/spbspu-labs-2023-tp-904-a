#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>

#include "parser.hpp"

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
  using isit = std::istream_iterator< turkin::Polygon >;
  std::deque< turkin::Polygon > data;

  while (!file.eof())
  {
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      continue;
    }
    std::copy(isit(file), isit(), std::back_inserter(data));
  }

  turkin::MakeCMD make;
  while (std::cin)
  {
    std::string type = "";
    std::cin >> type;
    if (!std::cin)
    {
      break;
    }
    try
    {
      std::string sub_info = "";
      getline(std::cin, sub_info);
      sub_info.erase(0, 1);
      std::cout << make.get_main().get(type)(data, make.get_sub(), type, sub_info) << "\n";
    }
    catch (...)
    {
      turkin::outInvalidCMD(std::cout);
      std::cout << "\n";
    }
  }
}
