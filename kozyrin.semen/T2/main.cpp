#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>
#include <deque>
#include "datastruct.h"

int main()
{
  using namespace kozyrin;
  using ist_iter = std::istream_iterator< DataStruct >;
  using ost_iter = std::ostream_iterator< DataStruct >;
  std::deque< DataStruct > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(ist_iter(std::cin), ist_iter(), std::back_inserter(data));
  }
  std::sort(data.begin(), data.end(), comp);
  std::copy(data.begin(), data.end(), ost_iter(std::cout, "\n"));
}
