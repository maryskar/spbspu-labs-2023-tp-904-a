#include <iostream>
#include <string>
#include <map>
#include "semanticTree.h"
#include "createMapOfCommands.h"

int main()
{
  using MapOfExpressions = std::map< std::string, mashkin::SemanticTree< std::string >* >;
  MapOfExpressions mapOfExpressions;
  std::map< std::string, void (*)(std::istream&, MapOfExpressions&) > mapOfCommands;
  try
  {
    createMapOfCommands(mapOfCommands);
    while (std::cin)
    {
      std::string command;
      std::cin >> command;
      if (mapOfCommands.find(command) != mapOfCommands.end())
      {
        mapOfCommands[command](std::cin, mapOfExpressions);
      }
      else
      {
        std::cerr << "<INVALID COMMAND>\n";
        return 1;
      }
    }
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what() << "\n";
    return 1;
  }
  return 0;
}
