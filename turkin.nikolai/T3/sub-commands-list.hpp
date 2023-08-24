#ifndef SUB_COMMANDS_LIST_HPP
#define SUB_COMMANDS_LIST_HPP

#include <map>

#include "sub-commands.hpp"

namespace turkin
{
  using sub_cmd_t = ReturnType (*)(data_t & data, std::istream &);
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

  std::map< std::string, sub_cmd_t > sub_maxseq_list
  {
    {"DEFAULT", maxseq_sub}
  };

  std::map< std::string, sub_cmd_t > sub_rightshapes_list
  {
    {"DEFAULT", rightshapes_sub}
  };
}
#endif
