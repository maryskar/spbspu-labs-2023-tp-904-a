#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>
#include "dataStruct.h"

int main()
{
  using gudkov::Data;

  std::vector< Data > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(
      std::istream_iterator< Data >(std::cin),
      std::istream_iterator< Data >(),
      std::back_inserter(data)
    );
  }

  std::sort(std::begin(data), std::end(data), gudkov::isLess);

  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< Data >(std::cout, "\n")
  );

  return 0;
}
