#include "DataStruct.hpp"
#include <iterator>
#include <algorithm>
#include <limits>
#include <deque>
int main()
{
  using inIter = std::istream_iterator< litvin::DataStruct >;
  using outIter = std::ostream_iterator< litvin::DataStruct >;
  std::deque< litvin::DataStruct> data;
  while (!std::cin.eof())
  {
    std::copy(inIter(std::cin), inIter(), std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end(), litvin::Compare{});
  std::copy(data.begin(), data.end(), outIter(std::cout, "\n"));
  return 0;
}
