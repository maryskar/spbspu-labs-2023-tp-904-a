#include <deque>
#include "DataStruct.h"
int main()
{
  std::deque< avdeeva::DataStruct > data;
  avdeeva::Comparator comparator;
  using inIter = std::istream_iterator< avdeeva::DataStruct >;
  while (!std::cin.eof())
  {
    std::copy(inIter(std::cin), inIter(), std::back_inserter(data));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
