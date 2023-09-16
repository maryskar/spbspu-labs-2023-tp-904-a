#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>
#include "DataStruct.h"

int main()
{
  using namespace zhdanov;
  std::vector< DataStruct > vector;
  auto firstCin = std::istream_iterator< DataStruct >(std::cin);
  auto endCin = std::istream_iterator< DataStruct >();
  std::copy(firstCin, endCin, std::back_inserter(vector));
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    auto firstCin = std::istream_iterator< DataStruct >(std::cin);
    auto endCin = std::istream_iterator< DataStruct >();
    std::copy(firstCin, endCin, std::back_inserter(vector));
  }
  std::sort(vector.begin(), vector.end());
  std::copy(vector.begin(), vector.end(), std::ostream_iterator< DataStruct >(std::cout, "\n"));
  return 0;
}
