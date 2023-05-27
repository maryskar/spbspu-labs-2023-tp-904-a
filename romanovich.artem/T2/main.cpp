#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "datastruct.h"
int main()
{
  std::vector< romanovich::DataStruct > dsVector;
  using iter = std::istream_iterator< romanovich::DataStruct >;
  auto target = std::back_inserter(dsVector);
  while (!std::cin.eof())
  {
    std::copy(iter(std::cin), iter(), target);
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  romanovich::Comparator Comp;
  std::sort(dsVector.begin(), dsVector.end(), Comp);
  std::copy(dsVector.begin(), dsVector.end(), std::ostream_iterator< romanovich::DataStruct >(std::cout, "\n"));
  return 0;
}
