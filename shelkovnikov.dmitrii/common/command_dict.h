#ifndef SPBSPU_LABS_2023_TP_904_COMMAND_DICT_H
#define SPBSPU_LABS_2023_TP_904_COMMAND_DICT_H
#include <vector>
#include <map>
#include <ostream>
#include <istream>
#include "polygon.h"
namespace dimkashelk
{
  using comm_t = void(*)(const std::vector< Polygon > &data, std::ostream &out);
  using comm_with_size_t = void(*)(const std::vector< Polygon > &data, std::ostream &out, size_t n);
  using comm_with_input_t = void(*)(const std::vector< Polygon > &data, std::ostream &out, std::istream &in);
  struct comm_dict_t
  {
    std::map< std::string, comm_t > dic1;
    std::map< std::string, comm_with_size_t > dic2;
    std::map< std::string, comm_with_input_t > dic3;
  };
  comm_dict_t createCommDict();
}
#endif
