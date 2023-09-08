#ifndef SUBCOMMANDSLIST_H
#define SUBCOMMANDSLIST_H
#include <map>
#include "subCommands.h"
namespace fesenko
{
  using sub_cmd_t = ReturnType (*)(data_t &data, std::istream &);
  std::map< std::string, sub_cmd_t > sub_area_list
  {
    {"ODD", area_odd},
    {"EVEN", area_even},
    {"MEAN", area_mean},
    {"VERTEXES", area_vertexes}
  };

  std::map< std::string, sub_cmd_t > sub_max_list
  {
    {"AREA", max_area},
    {"VERTEXES", max_vertexes}
  };

  std::map< std::string, sub_cmd_t > sub_min_list
  {
    {"AREA", min_area},
    {"VERTEXES", min_vertexes}
  };

  std::map< std::string, sub_cmd_t > sub_count_list
  {
    {"ODD", count_odd},
    {"EVEN", count_even},
    {"VERTEXES", count_vertexes}
  };

  std::map< std::string, sub_cmd_t > sub_rects_list
  {
    {"DEFAULT", rects_sub}
  };

  std::map< std::string, sub_cmd_t > sub_inframe_list
  {
    {"DEFAULT", inframe_sub}
  };
}
#endif
