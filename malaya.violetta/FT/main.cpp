#include <limits>
#include "helpFunctions.hpp"
int main()
{
  malaya::Commands comms;
  malaya::dictOfDicts data;
  malaya::descriptDict descriptions = malaya::makeDescriptDict();
  while (!std::cin.eof())
  {
    try
    {
      std::string command = malaya::inputCommand(std::cin);
      malaya::executeCommand(data, command, descriptions, comms, std::cout, std::cin);
    }
    catch (const std::runtime_error &)
    {
      break;
    }
    catch (const std::logic_error &)
    {
      malaya::printInvalid(std::cout);
      std::cout << '\n';
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
