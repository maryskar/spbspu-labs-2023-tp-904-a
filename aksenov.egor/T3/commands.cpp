#include "commands.h"
#include <iostream>
#include <vector>
#include <string>
#include "polygon.h"
namespace aksenov
{
  void doArea(std::istream &inp, const std::vector< Polygon > &pol)
  {
    std::string command = "";
    inp >> command;

    if (command == "EVEN")
    {
      doAreaEven(pol);
    }
    else if (command == "ODD")
    {
      doAreaOdd(pol);
    }
    else if (command == "MEAN")
    {
      doAreaMean(pol);
    }
    else if (isInteger(command))
    {
      if (command == "1" || command == "2")
      {
        std::cout << "error";
      }
      else
      {
        doAreaWithVertexes(pol, command);
      }
    }
  }
}
