#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>
#include "datastruct.h"
#include "comparator.h"

int main()
{
  using ds_t = tarasenko::DataStruct;
  std::vector< ds_t > data;
  using input_iter = std::istream_iterator< ds_t >;
  while (!std::cin.eof())
  {
    std::copy(input_iter(std::cin), input_iter(), std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  tarasenko::Comparator comp;
  using output_iter = std::ostream_iterator< ds_t >;
  std::sort(data.begin(), data.end(), comp);
  std::copy(data.begin(), data.end(), output_iter(std::cout, "\n"));
}
