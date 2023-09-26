#include <algorithm>
#include <iostream>
#include <deque>
#include <iterator>
#include "DataStruct.h"
#include "DataIO.h"
int main()
{
  std::deque< zhukova::DataStruct > dataVector;
  using in_iter = std::istream_iterator< zhukova::DataStruct >;
  while (!std::cin.eof())
  {
    std::copy(in_iter(std::cin), in_iter(), std::back_inserter(dataVector));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(std::begin(dataVector), std::end(dataVector), zhukova::Comparator());
  std::ostream_iterator< zhukova::DataStruct > out(std::cout, "\n");
  std::copy(std::begin(dataVector), std::end(dataVector), out);
  return 0;
}
