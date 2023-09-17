#include <iostream>
#include <vector>
#include <algorithm>
#include "dataStruct.h"

using namespace potapova;

int main()
{
  std::vector< DataStruct > data;
  while (!std::cin.eof())
  {
    std::copy(
    std::istream_iterator< DataStruct >(std::cin),
    std::istream_iterator< DataStruct >(),
    std::back_inserter(data)
    );
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(2147483647, '\n');
    }
  }

  std::sort(data.begin(), data.end(), Comparator());

  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );
  return 0;
}
