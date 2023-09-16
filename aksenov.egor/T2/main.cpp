#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>
#include "DataStruct.h"
#include "Comparator.h"
int main()
{
  std::vector< aksenov::DataStruct > data;
  using inputIter = std::istream_iterator< aksenov::DataStruct >;
  using outputIter = std::ostream_iterator< aksenov::DataStruct >;
  while (!std::cin.eof())
  {
    std::copy(inputIter(std::cin), inputIter(), std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end(), aksenov::toCompare);
  std::copy(data.begin(), data.end(), outputIter(std::cout, "\n"));
}
