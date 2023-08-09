#include "DataStruct.h"
#include <iterator>
#include <vector>

int main()
{
  using skalisusov::DataStruct;
  using skalisusov::comparate;
  std::vector< DataStruct > vectornanor;
   while(!std::cin.eof())
   {
  std::copy(
          std::istream_iterator< skalisusov::DataStruct >(std::cin),
          std::istream_iterator< skalisusov::DataStruct >(),
          std::back_inserter(vectornanor)
          );
   }
  std::sort(std::begin(vectornanor), std::end(vectornanor),comparate);
  std::copy(
          std::begin(vectornanor),
          std::end(vectornanor),
          std::ostream_iterator< skalisusov::DataStruct >(std::cout, "\n")
  );
  return 0;
}
