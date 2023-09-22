#include <iostream>
#include <deque>
#include <limits>
#include "dataStruct.h"

int main()
{
  std::deque< samoilenko::DataStruct > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n')
    }
  }
}