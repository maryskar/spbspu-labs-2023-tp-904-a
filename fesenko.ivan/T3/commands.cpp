#include "commands.h"
#include <sstream>
#include <cctype>
#include "subCommandsList.h"

std::ostream &fesenko::area(data_t &data, std::istream &in, std::ostream &out)
{
  std::string type = "";
  in >> type;
  if (std::isdigit(type[0])) {
    std::istringstream in(type);
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
  if (std::isdigit(type[0])) {
    std::istringstream in(type);
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

std::ostream &fesenko::inframe(data_t &data, std::istream &in, std::ostream &out)
{
  if (data.empty()) {
    throw std::logic_error("Data is empty");
  }
  return out << sub_inframe_list["DEFAULT"](data, in);
}
