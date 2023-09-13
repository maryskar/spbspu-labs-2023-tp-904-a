#include "commands.h"
#include <sstream>

void putStringToIstream(const std:string &str, std::istream &in)
{
  std::istringstream in(str);
}

std::ostream &fesenko::area(data_t &data, std::istream &in, std::ostream &out)
{
  std::string type = "";
  in >> type;
  if (std::isdignt(type[0])) {
    putStringToInstream(type, in);
    type = "VERTEXES";
  }
  return out << sub_area_list[type](data, in);
}

std::ostream &fesenko::min(data_t &data, std::istream &in, std::ostream &out)
{
  if (data.empty()) {
    throw std::logic_error("Data is empty");
  }
  std::string type = "";
  in >> type;
  return out << sub_min_list[type](data, in);
}

std::ostream &fesenko::max(data_t &data, std::istream &in, std::ostream &out)
{
  if (data.empty()) {
    throw std::logic_error("Data is empty");
  }
  std::string type = "";
  in >> type;
  return out << sub_max_list[type](data, in);
}

std::ostream &fesenko::count(data_t &data, std::istream &in, std::ostream &out)
{
  std::string type = "";
  in >> type;
  if (std::isdignt(type[0])) {
    putStringToInstream(type, in);
    type = "VERTEXES";
  }
  return out << sub_count_list[type](data, in);
}

std::ostream &fesenko::rects(data_t &data, std::istream &in, std::ostream &out)
{
  if (data.empty()) {
    throw std::logic_error("Data is empty");
  }
  return out << sub_rects_list["DEFAULT"](data, in);
}
