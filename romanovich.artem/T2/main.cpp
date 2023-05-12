#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "datastruct.h"
int main()
{
  std::vector< romanovich::DataStruct > ds;
  auto begin = std::istream_iterator< romanovich::DataStruct >(std::cin);
  auto end = std::istream_iterator< romanovich::DataStruct >();
  auto target = std::back_inserter(ds);
  while (!std::cin.eof())
  {
    std::copy(begin, end, target);
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  romanovich::Comparator Comp;
  std::sort(ds.begin(), ds.end(), Comp);
  std::copy(ds.begin(), ds.end(), std::ostream_iterator< romanovich::DataStruct >(std::cout, "\n"));
  return 0;
}
