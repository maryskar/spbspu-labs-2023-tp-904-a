#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include "DataStruct.hpp"
#include "InpOutTypes.hpp"

int main()
{
  std::vector<dataStruct> vector;
  dataStruct data; 
  while(!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(std::istream_iterator<dataStruct>(std::cin), std::istream_iterator<dataStruct>(), std::back_inserter(vector));
  }
  std::sort(vector.begin(), vector.end(), compare);
  std::copy(std::begin(vector), std::end(vector), std::ostream_iterator<dataStruct>(std::cout, "\n"));
}
