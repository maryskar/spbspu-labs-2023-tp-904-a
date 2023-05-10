#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include "dataStruct.h"

int main()
{
  std::vector< mashkin::DataStruct > res;
  mashkin::Comparator comp;
  while (!std::cin.eof())
  {
    std::copy(std::istream_iterator< mashkin::DataStruct >(std::cin), std::istream_iterator< mashkin::DataStruct >(),
        std::back_inserter(res));
    if (std::cin.fail())
    {
      std::string line;
      std::cin.clear();
      std::getline(std::cin, line);
    }
  }
  std::sort(std::begin(res), std::end(res), comp);
  std::copy(std::begin(res), std::end(res), std::ostream_iterator< mashkin::DataStruct >(std::cout, "\n"));
  return 0;
}
