#include <iostream>
#include "command_executor.h"

int main()
{
  kumachev::State globalState;
  kumachev::CommandSystem cs = kumachev::createCommandSystem();
  kumachev::CommandExecutor e(std::cin, std::cout, cs, globalState);

  while (std::cin.good()) {
    e.handleCommand();
  }

  return 0;
}
