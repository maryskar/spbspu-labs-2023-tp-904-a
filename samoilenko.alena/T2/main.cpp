#include <iostream>
#include <deque>
#include <limits>
#include <iterator>
#include "dataStruct.h"

int main()
{
  using iter_of_inp = std::istream_iterator< samoilenko::DataStruct >;
  std::deque< samoilenko::DataStruct > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}