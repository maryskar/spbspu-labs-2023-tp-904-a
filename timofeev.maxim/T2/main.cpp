#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>
#include "comparator.h"
#include "DataStruct.h"

int main()
{
  using tds = timofeev::DataStruct;
  using out = std::ostream_iterator< tds >;
  using iter = std::istream_iterator< tds>;
  std::vector< tds > data;
  timofeev::Comparator comparator;
  while(!std::cin.eof())
  {
    std::copy(iter(std::cin), iter(), std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end(), comparator);
  std::copy(data.begin(), data.end(), out(std::cout, "\n"));
  return 0;
}
