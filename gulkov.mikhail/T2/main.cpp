#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include "dataStruct.hpp"

int main()
{
  using namespace gulkov;
  using input_iterator = std::istream_iterator< DataStruct >;
  using output_iterator = std::ostream_iterator< DataStruct >;

  std::list< DataStruct > res_list;
  Comparator comparator;

  while (!std::cin.eof())
  {
    std::copy(input_iterator(std::cin), input_iterator(), std::back_inserter(res_list));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  res_list.sort(comparator);
  std::copy(std::begin(res_list), std::end(res_list), output_iterator(std::cout, "\n"));
}
