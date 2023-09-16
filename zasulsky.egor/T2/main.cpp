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
  dataStruct data
  while(!std::cin.eof())
  {
    std::copy(itInp(std::cin), itInp(), std::back_inserter(vector));
  }
  std::sort(vector.begin(), vector.end(), compare);
  std::copy(vector.begin(), vector.end(), itOut(std::cout));
}
