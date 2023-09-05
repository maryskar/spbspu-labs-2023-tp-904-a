#include <vector>
#include <iterator>
#include <algorithm>
#include "DataStruct.h"

int main()
{
  using skalisusov::DataStruct;
  using InpIter = std::istream_iterator< DataStruct >;
  using OutpIter = std::ostream_iterator< DataStruct >;
  std::vector< DataStruct > vector;
  while (!std::cin.eof())
  {
    std::copy(InpIter(std::cin),
      InpIter(),
      std::back_inserter(vector));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(std::begin(vector), std::end(vector), skalisusov::comparator);
  std::copy(std::begin(vector),
    std::end(vector),
    OutpIter(std::cout, "\n"));
  return 0;
}
