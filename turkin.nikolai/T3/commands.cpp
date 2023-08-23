#include "commands.hpp"

#include <iostream>
#include <functional>
#include <numeric>
#include <cmath>
#include "point-struct.hpp"
#include "area-calc.hpp"

std::ostream & turkin::area(std::vector< Polygon > & data, std::istream & in, std::ostream & out)
{
  std::string type;
  in >> type;
  if (type == "ODD")
  {
    out << std::accumulate(data.cbegin(), data.cend(), 0.0, oddArea);
  }
  else if (type == "EVEN")
  {
    out << std::accumulate(data.cbegin(), data.cend(), 0.0, evenArea);
  }
  return out;
}

std::ostream & turkin::min(std::vector< Polygon > & data, std::istream & in, std::ostream & out)
{
  out << "min";
  in >> data.back();
  return out;
}

std::ostream & turkin::max(std::vector< Polygon > & data, std::istream & in, std::ostream & out)
{
  out << "max";
  in >> data.back();
  return out;
}

std::ostream & turkin::count(std::vector< Polygon > & data, std::istream & in, std::ostream & out)
{
  out << "count";
  in >> data.back();
  return out;
}

std::ostream & turkin::maxseq(std::vector< Polygon > & data, std::istream & in, std::ostream & out)
{
  out << "maxseq";
  in >> data.back();
  return out;
}

std::ostream & turkin::rightshapes(std::vector< Polygon > & data, std::istream & in, std::ostream & out)
{
  out << "rightshapes";
  in >> data.back();
  return out;
}
