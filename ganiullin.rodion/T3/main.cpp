// IN FRAME   SAME
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include "Commands.h"
#include "Geometry.h"

int main()
{
  using inIter = std::istream_iterator< ganiullin::Polygon >;
  auto outIter = std::ostream_iterator< ganiullin::Polygon >(std::cout, "\n");
  std::vector< ganiullin::Polygon > polygons;
  std::istringstream iss(
    "3 (0;1) (3;4) (5;0)"
    "4 (0;0) (0;1) (1;0) (1;1)");
  std::istringstream testFrame(
    "3 (0;0) (-3;-4) (4;2)"
    "4 (1;2) (4;0) (5;1) (0;3)");
  std::istringstream testSame(
    "3 (-6;11) (-3;14) (-1;10)"
    "4 (0;1) (0;1) (1;0) (1;1)");
  ganiullin::Polygon Yes;
  ganiullin::Polygon No;
  std::copy(inIter(iss), inIter(), std::back_inserter(polygons));
  std::copy(std::begin(polygons), std::end(polygons), outIter);
  std::cout << "9 == " << ganiullin::getPolygonArea(polygons[0]) << '\n';
  std::cout << "1 == " << ganiullin::getPolygonArea(polygons[1]) << '\n';
  testFrame >> No >> Yes;
  std::cout << "false == " << std::boolalpha << ganiullin::isInFrame(No, polygons) << '\n';
  std::cout << "true == " << std::boolalpha << ganiullin::isInFrame(Yes, polygons) << '\n';

  ganiullin::Polygon one;
  ganiullin::Polygon zero;
  testSame >> one >> zero;
  std::cout << "1 == " << ganiullin::countSame(one, polygons) << '\n';
  std::cout << "0 == " << ganiullin::countSame(zero, polygons) << '\n';
}
