#ifndef T3_FUNCS_FOR_MAP_COMMANDS_H
#define T3_FUNCS_FOR_MAP_COMMANDS_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <functional>
#include <message.h>
#include "funcs_for_commands.h"

namespace tarasenko
{
  using data_t = std::deque< Polygon >;

  std::ostream& getAreaWithEqualNumVertsCommand(const data_t& data,
     std::istream& in, std::ostream& out)
  {
    size_t n = 0;
    in >> n;
    return out << std::fixed << std::setprecision(1) << getAreaWithEqualNumVerts(data, n);
  }

  std::ostream& getNumWithEqualNumVertsCommand(const data_t& data,
     std::istream& in, std::ostream& out)
  {
    size_t n = 0;
    in >> n;
    return out << getNumWithEqualNumVerts(data, n);
  }

  std::ostream& getAreaEvenCommand(const data_t& data, std::ostream& out)
  {
    return out << std::fixed << std::setprecision(1) << getAreaEven(data);
  }

  std::ostream& getAreaOddCommand(const data_t& data, std::ostream& out)
  {
    return out << std::fixed << std::setprecision(1) << getAreaOdd(data);
  }

  std::ostream& getAreaMeanCommand(const data_t& data, std::ostream& out)
  {
    return out << std::fixed << std::setprecision(1) << getAreaMean(data);
  }

  std::ostream& getMaxAreaCommand(const data_t& data, std::ostream& out)
  {
    return out << std::fixed << std::setprecision(1) << getMaxArea(data);
  }

  std::ostream& getMinAreaCommand(const data_t& data, std::ostream& out)
  {
    return out << std::fixed << std::setprecision(1) << getMinArea(data);
  }

  std::ostream& getMaxVertsCommand(const data_t& data, std::ostream& out)
  {
    return out << getMaxVerts(data);
  }

  std::ostream& getMinVertsCommand(const data_t& data, std::ostream& out)
  {
    return out << getMinVerts(data);
  }

  std::ostream& getNumEvenCommand(const data_t& data, std::ostream& out)
  {
    return out << getNumEven(data);
  }

  std::ostream& getNumOddCommand(const data_t& data, std::ostream& out)
  {
    return out << getNumOdd(data);
  }

  std::ostream& getNumRightShapesCommand(const data_t& data, std::ostream& out)
  {
    return out << getNumRightShapes(data);
  }

  std::ostream& isInFrameCommand(const data_t& data,
     std::istream& in, std::ostream& out)
  {
    Polygon polygon;
    getFrameRect(in, polygon);
    return out << (isInFrame(data, polygon) ? "<TRUE>" : "<FALSE>");
  }
}
#endif
