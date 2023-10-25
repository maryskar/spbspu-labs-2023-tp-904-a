#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <list>

#include "DataStruct.hpp"

int main()
{
  using IIt = std::istream_iterator< kabanov::DataStruct >;
  using OIt = std::ostream_iterator< kabanov::DataStruct >;
  std::list< kabanov::DataStruct > structs;
  while (!std::cin.eof())
  {
    std::copy(IIt(std::cin), IIt(), std::back_inserter(structs));
    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  structs.sort(kabanov::comp);
  std::copy(structs.begin(), structs.end(), OIt(std::cout, "\n"));
  return EXIT_SUCCESS;
}
