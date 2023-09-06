#include "commands.hpp"

#include <algorithm>
#include <cctype>
#include <numeric>
#include <string>

#include "sub-commands-list.hpp"

namespace
{
  void put_string(const std::string & str, std::istream & in)
  {
    auto temp = str;
    std::reverse(temp.begin(), temp.end());
    for (auto it : temp) in.putback(it);
  }
}

std::ostream & turkin::area(data_t & data, std::istream & in, std::ostream & out)
{
  std::string type = "";
  in >> type;
  if (std::isdigit(type[0]))
  {
    put_string(type, in);
    type = "VERTEXES";
  }
  return out << sub_area_list[type](data, in);
}

std::ostream & turkin::min(data_t & data, std::istream & in, std::ostream & out)
{
  if (data.empty())
  {
    throw std::runtime_error("empty source");
  }
  std::string type = "";
  in >> type;
  return out << sub_min_list[type](data, in);
}

std::ostream & turkin::max(data_t & data, std::istream & in, std::ostream & out)
{
  if (data.empty())
  {
    throw std::runtime_error("empty source");
  }
  std::string type = "";
  in >> type;
  return out << sub_max_list[type](data, in);
}

std::ostream & turkin::count(data_t & data, std::istream & in, std::ostream & out)
{
  std::string type = "";
  in >> type;
  if (std::isdigit(type[0]))
  {
    put_string(type, in);
    type = "VERTEXES";
  }
  return out << sub_count_list[type](data, in);
}

std::ostream & turkin::maxseq(data_t & data, std::istream & in, std::ostream & out)
{
  if (data.empty())
  {
    throw std::runtime_error("empty source");
  }
  return out << sub_maxseq_list["DEFAULT"](data, in);
}

std::ostream & turkin::rightshapes(data_t & data, std::istream & in, std::ostream & out)
{
  if (data.empty())
  {
    throw std::runtime_error("empty source");
  }
  return out << sub_rightshapes_list["DEFAULT"](data, in);
}
