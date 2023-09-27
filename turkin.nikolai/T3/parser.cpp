#include "parser.hpp"
#include <ostream>
#include <iostream>

turkin::MakeCMD::MakeCMD():
  main_list_(),
  sub_list_()
{}

std::ostream & turkin::MakeCMD::operator()(std::deque< Polygon > & data, std::istream & in, std::ostream & out)
{
  std::string type = "";
  std::string sub_info = "";
  in >> type;
  in >> sub_info;
  if (!in)
  {
    return out;
  }
  return out << main_list_.get(type)(data, sub_list_, type, sub_info);
}
