#include <iostream>
#include <vector>
#include "dataStruct.h"

using namespace potapova;

int main()
{
  std::vector< DataStruct > data;
  std::copy(
    std::istream_iterator< DataStruct >(std::cin),
    std::istream_iterator< DataStruct >(),
    std::back_inserter(data)
  );

  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );
  return 0;
}
