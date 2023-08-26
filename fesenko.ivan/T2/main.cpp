#include <deque>
#include <iterator>
#include <limits>
#include <algorithm>
#include "dataStruct.h"

int main()
{
  using in_iter = std::istream_iterator< fesenko::DataStruct >;
  using out_iter = std::ostream_iterator< fesenko::DataStruct >;
  std::deque< fesenko::DataStruct > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(in_iter(std::cin), in_iter(), std::back_inserter(data));
  }
  std::sort(data.begin(), data.end(), fesenko::compare);
  std::copy(std::begin(data), std::end(data), out_iter(std::cout, "\n"));
}
