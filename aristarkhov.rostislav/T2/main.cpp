#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include "dataStruct.h"

int main()
{

  using inputIterator = std::istream_iterator< aristarkhov::DataStruct >;
  using outputIterator = std::ostream_iterator< aristarkhov::DataStruct >;
  std::vector< aristarkhov::DataStruct > data;

  while (!std::cin.eof())
  {
    std::copy(inputIterator(std::cin), inputIterator(), back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end(), aristarkhov::compare);
  std::copy(data.begin(), data.end(), outputIterator(std::cout, "\n"));
  return 0;
}
