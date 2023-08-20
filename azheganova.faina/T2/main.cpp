#include <deque>
#include <iterator>
#include <algorithm>
#include <limits>
#include "datastruct.h"

int main()
{
  using ist_iter = std::istream_iterator< azheganova::DataStruct >;
  using ost_iter = std::ostream_iterator< azheganova::DataStruct >;
  std::deque< azheganova::DataStruct > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(ist_iter(std::cin), ist_iter(), std::back_inserter(data));
  }
  std::sort(data.begin(), data.end(), azheganova::compareValues);
  std::copy(std::begin(data), std::end(data), ost_iter(std::cout, "\n"));
  return 0;
}

