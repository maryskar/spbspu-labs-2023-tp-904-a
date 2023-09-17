#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>

#include "data-types.hpp"
#include "commands-list.hpp"
#include <out-msg.hpp>

int main()
{
  turkin::base_t base;
  while (std::cin)
  {
    std::string cmd;
    std::cin >> cmd;
    if (!std::cin)
    {
      break;
    }
    try
    {
      turkin::main_list.at(cmd)(base, std::cin, std::cout) << "\n";
    }
    catch (...)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      turkin::outInvalidCMD(std::cout);
    }
  }
}
