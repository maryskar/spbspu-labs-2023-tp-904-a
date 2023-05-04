#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "DataStruct.h"

constexpr size_t CHARS_TO_IGNORE = std::numeric_limits< std::streamsize >::max();

int main()
{
  auto inIterBegin = std::istream_iterator< ganiullin::DataStruct >(std::cin);
  auto inIterEnd = std::istream_iterator< ganiullin::DataStruct >();
  auto outIter = std::ostream_iterator< ganiullin::DataStruct >(std::cout, "\n");
  std::vector< ganiullin::DataStruct > data;
  ganiullin::Comparator comparator;

  while (!std::cin.eof()) {
    std::copy(inIterBegin, inIterEnd, std::back_inserter(data));

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(CHARS_TO_IGNORE, '\n');
    }
  }

  std::sort(data.begin(), data.end(), comparator);

  std::copy(std::begin(data), std::end(data), outIter);

  return 0;
}
