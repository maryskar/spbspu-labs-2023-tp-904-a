#include <iostream>
#include "command_executor.h"

int main()
{
  kumachev::State globalState;
  kumachev::CommandSystem cs = kumachev::createCommandSystem();
  kumachev::CommandExecutor e(std::cin, std::cout, cs, globalState, true);

  while (std::cin.good()) {
    try {
      e.handleCommand();
    }
    catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
    }
  }

  return 0;
}
