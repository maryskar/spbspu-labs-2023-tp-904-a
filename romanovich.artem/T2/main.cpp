#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include "datastruct.h"
int main()
{
  std::vector< romanovich::DataStruct > ds;
  std::back_insert_iterator< typeof(ds) > backInserter = std::back_inserter(ds);
  while (!std::cin.eof())
  {
    romanovich::DataStruct dataStruct;
    std::cin >> dataStruct;
    if (!std::cin.fail())
    {
      *backInserter = dataStruct;
      ++backInserter;
    }
  }
  std::sort(ds.begin(), ds.end(), romanovich::DataStruct::compareK3);
  std::sort(ds.begin(), ds.end(), romanovich::DataStruct::compareK2);
  std::sort(ds.begin(), ds.end(), romanovich::DataStruct::compareK1);
  std::for_each(ds.begin(), ds.end(), romanovich::DataStruct::print);
  return 0;
}
