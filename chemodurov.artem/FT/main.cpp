#include <iostream>
#include <limits>
#include <functional>
#include "do-command.hpp"

int main()
{
  chemodurov::CommandsMaps cmds{};
  chemodurov::DictWithFreqDicts data{};
  using namespace std::placeholders;
  auto do_comm_ptr = chemodurov::doCommandFromMaps;
  auto readComm = std::bind(chemodurov::readCommand, std::ref(std::cin));
  auto doComm = std::bind(do_comm_ptr, _1, std::cref(cmds), std::ref(std::cin), std::ref(std::cout), std::ref(data));
  auto outInvalid = std::bind(chemodurov::outInvalidCommand, std::ref(std::cout));
  constexpr auto max_size = std::numeric_limits< std::streamsize >::max();
  while (!std::cin.eof())
  {
    try
    {
      doComm(readComm());
    }
    catch (const std::logic_error & e)
    {
      outInvalid();
      std::cout << '\n';
      std::cin.clear();
      std::cin.ignore(max_size, '\n');
      continue;
    }
    catch (const std::runtime_error & e)
    {
      break;
    }
  }
  return 0;
}
