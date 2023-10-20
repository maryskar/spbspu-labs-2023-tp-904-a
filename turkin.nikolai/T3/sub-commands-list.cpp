#include "sub-commands-list.hpp"

turkin::SubCommandsList::SubCommandsList():
  list_({
    {"AREA", {{"ODD", area_odd}, {"EVEN", area_even}, {"MEAN", area_mean}, {"VERTEXES", area_vertexes}}},
    {"MAX", {{"AREA", max_area}, {"VERTEXES", max_vertexes}}},
    {"MIN", {{"AREA", min_area}, {"VERTEXES", min_vertexes}}},
    {"COUNT", {{"ODD", count_odd}, {"EVEN", count_even}, {"VERTEXES", count_vertexes}}},
    {"MAXSEQ", {{"POLYGON", maxseq_sub}}},
    {"RIGHTSHAPES", {{"NONTYPE", rightshapes_sub}}}
  })
{}

turkin::sub_inside_map_t & turkin::SubCommandsList::get(const std::string & type)
{
  return list_.at(type);
}
