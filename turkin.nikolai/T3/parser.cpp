#include "parser.hpp"

#include <ostream>
#include <vector>

#include "str-work.hpp"

turkin::MakeCMD::MakeCMD():
  main_list_(),
  sub_list_()
{}

std::ostream & turkin::MakeCMD::operator()(std::deque< Polygon > & data, std::istream & in, std::ostream & out)
{
  std::string cmd = "";
  std::string type = "";
  std::string sub_info = "";
  getline(in, cmd);
  std::vector< std::string > result = split_str(cmd, " ");
  type = result[0];
  if (result.size() == 2)
  {
    sub_info = result[1];
  }
  if (!in)
  {
    return out;
  }
  return out << main_list_.get(type)(data, sub_list_, type, sub_info);
}
