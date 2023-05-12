#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "datastruct.h"
int main()
{
  std::vector< romanovich::DataStruct > dsVector;
  using begin = std::istream_iterator< romanovich::DataStruct >;
  auto end = std::istream_iterator< romanovich::DataStruct >();
  auto target = std::back_inserter(dsVector);
  while (!std::cin.eof())
  {
    std::copy(begin(std::cin), end, target);
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  romanovich::Comparator Comp;
  std::sort(dsVector.begin(), dsVector.end(), Comp);
  std::copy(dsVector.begin(), dsVector.end(), std::ostream_iterator< romanovich::DataStruct >(std::cout));
  return 0;
}
