#include <iostream>
#include <algorithm>
#include <iterator>
#include <limits>
#include <deque>
#include "dataSrtuct.h"
#include "io.h"

using namespace muhortov;

int main()
{
  std::deque< DataStruct > data;
  while (!std::cin.eof()) {
    std::copy(std::istream_iterator< DataStruct >(std::cin),
      std::istream_iterator< DataStruct >(),
      std::back_inserter(data)
      );
    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end(), compare);
  std::copy(std::begin(data), std::end(data), std::ostream_iterator< DataStruct >(std::cout, "\n"));
  return 0;
}
