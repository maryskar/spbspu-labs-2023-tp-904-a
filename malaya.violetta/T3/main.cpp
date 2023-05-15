#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <limits>
#include "Polygon.hpp"
#include "getArea.hpp"

int main()
{
  std::ifstream in ("input.txt");
  using inIter = std::istream_iterator< malaya::Polygon >;
  std::vector< malaya::Polygon > data;
  std::copy(inIter(in), inIter(), std::back_inserter(data));
  std::string command;
  while(!std::cin.eof())
  {
    std::cin >> command;
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      continue;
    }
    else if(command == "AREA")
    {

    }
    else if(command == "MAX")
    {

    }
    else if(command == "MIN")
    {

    }
    else if(command == "COUNT")
    {

    }
    else if(command == "PERMS")
    {

    }
    else if(command == "RECTS")
    {

    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      continue;
    }
  }
  return 0;
}
