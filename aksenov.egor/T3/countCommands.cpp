#include "countFunctions.h"
#include <iostream>
#include <functional>
#include "helpFunctions.h"
namespace aksenov
{
  void doCountEven(const std::vector< Polygon > &pol)
  {
    std::vector< Polygon > pols = pol;
    size_t res = std::count_if(pols.begin(), pols.end(), isEven);
    std::cout << res << "\n";
  }

  void doCountOdd(const std::vector< Polygon > &pol)
  {
    std::vector< Polygon > pols = pol;
    size_t res = std::count_if(pols.begin(), pols.end(), isOdd);
    std::cout << res << "\n";
  }

  void doCountVertexes(std::string command, const std::vector< Polygon > &pol)
  {
    if (command == "1" || command == "2" || command == "0")
    {
      throw std::invalid_argument("invalid input");
    }
    std::vector< Polygon > pols = pol;
    size_t amount = std::stoull(command);
    auto func = std::bind(isEqual, std::placeholders::_1, amount);
    size_t res = std::count_if(pols.begin(), pols.end(), func);
    std::cout << res << "\n";
  }
}
