#include "commands.hpp"
#include "dictionary.hpp"
#include <iostream>



int main()
{
  Dictionary dict;
  while (!std::cin.eof())
  {
    try
    {
      createSet(dict, std::cin);
      for (const auto& pair : dict.dict_) {
        std::cout << pair.first << " : " << pair.second << std::endl;
      }
      std::cout << "dasdam\n";
      threeMostPopular(dict, std::cout);
    }
    catch (const std::runtime_error&)
    {
      break;
    }
  }
  return 0;
}