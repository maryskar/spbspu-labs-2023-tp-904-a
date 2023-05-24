#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <list>

#include "DataStruct.hpp"

int main()
{
  using IIt = std::istream_iterator< ilyak::DataStruct >;
  using OIt = std::ostream_iterator< ilyak::DataStruct >;
  std::list< ilyak::DataStruct > structs;
  while (!std::cin.eof())
  {
    std::copy(IIt(std::cin), IIt(), std::back_inserter(structs));
    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  structs.sort(ilyak::comp);
  std::copy(structs.begin(), structs.end(), OIt(std::cout, "\n"));
  return EXIT_SUCCESS;
}
