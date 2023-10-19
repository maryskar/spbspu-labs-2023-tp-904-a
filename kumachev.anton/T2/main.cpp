#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <iterator>
#include "data_struct.h"
#include "io.h"

int main()
{
  using inputIterator = std::istream_iterator< kumachev::DataStruct >;
  using outputIterator = std::ostream_iterator< kumachev::DataStruct >;

  std::vector< kumachev::DataStruct > data;
  auto backInserter = std::back_inserter(data);
  std::istream &in = std::cin;

  while (!in.eof()) {
    std::copy(inputIterator(std::cin), inputIterator(), backInserter);

    if (in.fail()) {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end(), kumachev::DataStructComparator{});
  std::copy(data.begin(), data.end(), outputIterator(std::cout, "\n"));

  return 0;
}
