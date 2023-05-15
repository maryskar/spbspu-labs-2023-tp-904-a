#include <iostream>
#include <fstream>
#include <iterator>
#include "polygon.hpp"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Not correct number of CML args\n";
    return 1;
  }
  std::ifstream ifstream(argv[1]);
  if (!ifstream.is_open())
  {
    std::cerr << "The file doesn't open\n";
    return 1;
  }

  std::vector< chemodurov::Polygon > data;
  while (!ifstream.eof())
  {
    if (ifstream.fail())
    {
      ifstream.clear();
      std::string line;
      std::getline(ifstream, line);
    }
    using is_it_t = std::istream_iterator< chemodurov::Polygon >;
    std::copy(is_it_t(ifstream), is_it_t(), std::back_inserter(data));
  }
  return 0;
}
