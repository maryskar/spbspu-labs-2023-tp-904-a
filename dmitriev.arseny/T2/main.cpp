#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "datastruct.h"

int main()
{
  using data_t = dmitriev::DataStruct;
  using iIter = std::istream_iterator< data_t >;
  using oIter = std::ostream_iterator< data_t >;

  std::vector< data_t > vec;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(iIter(std::cin), iIter(), std::back_inserter(vec));
  }
  std::sort(vec.begin(), vec.end(), dmitriev::compareDataStructures);
  std::copy(std::begin(vec), std::end(vec), oIter(std::cout, "\n"));

  return 0;
}
