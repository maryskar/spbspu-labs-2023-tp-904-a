#include "commands.h"
#include <algorithm>
#include <numeric>

bool vagina::isEven(const Polygon & pol)
{
  return (pol.points.size() % 2 == 0);
}

void vagina::areaEven(const std::vector< Polygon >& dest, std::ostream& out)
{
  std::vector< Polygon > tmp;
  std::copy_if(dest.begin(), dest.end(), tmp.begin(),
    [&](Polygon i) { return isEven(i); });
  std::vector< double > tmpS(tmp.size());
  std::transform(tmp.begin(), tmp.end(), tmpS.begin(), getArea);
  out << std::setprecision(1) << std::accumulate(tmpS.begin(), tmpS.end(), 0.0) << "\n";
}

void vagina::areaOdd(const std::vector< Polygon >& dest, std::ostream& out)
{
  std::vector< Polygon > tmp;
  std::copy_if(dest.begin(), dest.end(), tmp.begin(),
    [&](Polygon i) { return !isEven(i); });
  std::vector< double > tmpS(tmp.size());
  std::transform(tmp.begin(), tmp.end(), tmpS.begin(), getArea);
  out << std::setprecision(1) << std::accumulate(tmpS.begin(), tmpS.end(), 0.0) << "\n";
}
