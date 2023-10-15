#include "commands.hpp"

#include <algorithm>
#include <cctype>
#include <numeric>
#include <string>

#include "data-structs.hpp"
#include "sub-commands-list.hpp"

turkin::ReturnType turkin::area(data_t & data, SubCommandsList & list, std::string & type, std::string & sub_info)
{
  sub_inside_map_t ins = list.get(type);
  if (std::isdigit(sub_info[0]))
  {
    return ins["VERTEXES"](data, sub_info);
  }
  return ins[sub_info](data, sub_info);
}

turkin::ReturnType turkin::min(data_t & data, SubCommandsList & list, std::string & type, std::string & sub_info)
{
  if (data.empty())
  {
    throw std::runtime_error("empty source");
  }
  sub_inside_map_t ins = list.get(type);
  return ins[sub_info](data, sub_info);
}

turkin::ReturnType turkin::max(data_t & data, SubCommandsList & list, std::string & type, std::string & sub_info)
{
  if (data.empty())
  {
    throw std::runtime_error("empty source");
  }
  sub_inside_map_t ins = list.get(type);
  return ins[sub_info](data, sub_info);
}

turkin::ReturnType turkin::count(data_t & data, SubCommandsList & list, std::string & type, std::string & sub_info)
{
  sub_inside_map_t ins = list.get(type);
  if (std::isdigit(sub_info[0]))
  {
    return ins["VERTEXES"](data, sub_info);
  }
  return ins[sub_info](data, sub_info);
}

turkin::ReturnType turkin::maxseq(data_t & data, SubCommandsList & list, std::string & type, std::string & sub_info)
{
  if (data.empty())
  {
    throw std::runtime_error("empty source");
  }
  sub_inside_map_t ins = list.get(type);
  return ins["POLYGON"](data, sub_info);
}

turkin::ReturnType turkin::rightshapes(data_t & data, SubCommandsList & list, std::string & type, std::string & sub_info)
{
  if (data.empty())
  {
    throw std::runtime_error("empty source");
  }
  sub_inside_map_t ins = list.get(type);
  return ins["NONTYPE"](data, sub_info);
}
