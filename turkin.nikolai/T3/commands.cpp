#include "commands.hpp"

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

#include "point-struct.hpp"
#include "area-calc.hpp"

std::ostream & turkin::area(std::vector< Polygon > & data, std::istream & in, std::ostream & out)
{
  std::vector< Polygon > temp;
  std::string type;
  in >> type;
  if (type == "ODD")
  {
    std::copy_if(data.begin(), data.end(), std::back_inserter(temp), isOdd());
  }
  else if (type == "EVEN")
  {
    std::copy_if(data.begin(), data.end(), std::back_inserter(temp), isEven());
  }
  else
  {
    std::copy_if(data.begin(), data.end(), std::back_inserter(temp), isNum(std::stoul(type)));
  }
  return out << std::accumulate(temp.cbegin(), temp.cend(), 0.0, calcArea);
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
