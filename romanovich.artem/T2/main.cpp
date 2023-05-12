#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "datastruct.h"
bool isValid(const romanovich::DataStruct &)
{
  if (std::cin.fail())
  {
    std::cin.clear();
    std::string dummy;
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    return false;
  }
  return true;
}
int main()
{
  std::vector< romanovich::DataStruct > ds;
  std::back_insert_iterator< decltype(ds) > backInserter = std::back_inserter(ds);
  auto begin = std::istream_iterator< romanovich::DataStruct >(std::cin);
  auto end = std::istream_iterator< romanovich::DataStruct >();
  auto target = std::back_inserter(ds);
  std::copy_if(begin, end, target, isValid);
  romanovich::Comparator Comp;
  std::sort(ds.begin(), ds.end(), Comp);
  std::copy(ds.begin(), ds.end(), std::ostream_iterator< romanovich::DataStruct >(std::cout));
  return 0;
}
