#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include "DataStruct.hpp"
#include "InpOutTypes.hpp"

int main()
{
  using itOut = std::ostream_iterator<dataStruct>;
  using itInp = std::istream_iterator<dataStruct>;
  std::vector<dataStruct> vector;
  dataStruct data;

  while(!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(itInp(std::cin), itInp(), std::back_inserter(vector));
  }
  std::sort(vector.begin(), vector.end(), compare);
  std::copy(std::begin(vector),std::end(vector), itOut(std::cout, "\n"));
}
