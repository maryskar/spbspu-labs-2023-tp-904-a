#include <iostream>
#include "command_executor.h"

int main()
{
  kumachev::State globalState;
  kumachev::CommandExecutor globalExecutor(std::cin, std::cout, globalState, true);
  globalExecutor.execute();
  return 0;
}
