#ifndef SPBSPU_LABS_2023_TP_904_COMMAND_DICT_H
#define SPBSPU_LABS_2023_TP_904_COMMAND_DICT_H
#include <vector>
#include <map>
#include <ostream>
#include <istream>
#include "polygon.h"
namespace dimkashelk
{
  class CommandContainer
  {
  using comm_t = void(*)(const std::vector< Polygon > &data, std::ostream &out);
  using comm_with_size_t = void(*)(const std::vector< Polygon > &data, std::ostream &out, size_t n);
  using comm_with_input_t = void(*)(const std::vector< Polygon > &data, std::ostream &out, std::istream &in);
  public:
    CommandContainer();
  private:
    std::map< std::string, comm_t > dict_simple_command_;
    std::map< std::string, comm_with_size_t > dict_with_size_t_command_;
    std::map< std::string, comm_with_input_t > dict_with_input_command_;
    std::map< std::string, comm_t > initializeSimpleCommand();
    std::map< std::string, comm_with_size_t > initializeSizeTCommand();
    std::map< std::string, comm_with_input_t > initializeInputCommand();
  };
  //comm_dict_t createCommDict();
}
#endif
