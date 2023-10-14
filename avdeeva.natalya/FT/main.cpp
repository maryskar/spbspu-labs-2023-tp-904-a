#include <functional>
#include <iterator>
#include <limits>
#include "outCommand.h"

int main()
{
  using mapOfGraphs = std::map< std::string, avdeeva::Graph >;
  using cmdType = std::function< void(mapOfGraphs &, std::istream &, std::ostream &) >;
  std::map< std::string, cmdType > commands;
  commands.insert({ "CREATE", avdeeva::createGraphCommand });
  commands.insert({ "UNION", avdeeva::getUnionCommand });
  commands.insert({ "INSERT", avdeeva::insertVertCommand });
  commands.insert({ "RENAME", avdeeva::renameVertCommand });
  commands.insert({ "DELETE", avdeeva::deleteVertCommand });
  commands.insert({ "DIJKSTRA", avdeeva::dijkstraCommand });
  commands.insert({ "BELLMAN_FORD", avdeeva::bellmanFordCommand });
  commands.insert({ "WAVE", avdeeva::waveAlgCommand });
  commands.insert({ "CHECK_NODES", avdeeva::checkNodesCommand });
  commands.insert({ "CHECK_NODE", avdeeva::checkNodeCommand });
  commands.insert({ "CHECK_ARC", avdeeva::checkArcCommand });
  commands.insert({ "PRINT_LIST", avdeeva::printListCommand });
  commands.insert({ "PRINT_MATRIX", avdeeva::printMatrixCommand });
  mapOfGraphs graphs;
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::string command;
    std::cin >> command;
    if (command == "HELP")
    {
      avdeeva::helpCommand(std::cout);
    }
    try
    {
      commands.at(command)(graphs, std::cin, std::cout);
    }
    catch (const std::exception & e)
    {
      std::cout << "INVALID COMMAND" << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
