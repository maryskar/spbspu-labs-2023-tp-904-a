#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>
#include "dataStruct.h"

int main()
{
  std::vector< mashkin::DataStruct > res;
  //mashkin::DataStruct data;
  mashkin::Comparator comp;
  using inpIter = std::istream_iterator< mashkin::DataStruct >;
  using outIter = std::ostream_iterator< mashkin::DataStruct >;
  constexpr auto maxSize = std::numeric_limits< std::streamsize >::max();
  while (!std::cin.eof())
  {
    //std::cin >> data;
    std::copy(inpIter(std::cin), inpIter(), std::back_inserter(res));
    if (std::cin.fail())
    {
      // std::string line;
      std::cin.clear();
      std::cin.ignore(maxSize, '\n');
      // std::getline(std::cin, line);
    }
  }
  std::sort(std::begin(res), std::end(res), comp);
  std::copy(std::begin(res), std::end(res), outIter(std::cout, "\n"));
  return 0;
}
