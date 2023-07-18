#include "commands.hpp"
#include <vector>
#include "polygon.hpp"
namespace litvin
{
  using v_polygon = std::vector< litvin::Polygon >;
  bool isEven(const Polygon & polygon)
  {
    return (size(polygon) % 2 == 0);
  }
  size_t getSumArea(const v_polygon & data)
  {
    size_t res = 0;
    return res;
  }
}
