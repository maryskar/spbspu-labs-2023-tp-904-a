#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <iterator>
#include "datastruct.h"
int main()
{
  std::vector< romanovich::DataStruct > ds;
  std::back_insert_iterator< decltype(ds) > backInserter = std::back_inserter(ds);
  while (!std::cin.eof())
  {
    romanovich::DataStruct dataStruct;
    std::cin >> dataStruct;
    if (!std::cin.fail())
    {
      *backInserter = dataStruct;
      ++backInserter;
    }
    else
    {
      std::cin.clear();
      std::string dummy;
      std::getline(std::cin, dummy);
    }
  }
  romanovich::Comparator Comp;
  std::sort(ds.begin(), ds.end(), Comp);
  std::copy(ds.begin(), ds.end(), std::ostream_iterator< romanovich::DataStruct >(std::cout));
  return 0;
}
