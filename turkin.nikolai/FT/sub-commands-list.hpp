#ifndef SUB_COMMANDS_LIST_HPP
#define SUB_COMMANDS_LIST_HPP

#include "sub-commands.hpp"

namespace turkin
{
  func_t sub_add_list
  {
    {"DICT", add_dict},
    {"WORD", add_word},
    {"TRNS", add_trns}
  };

  func_t sub_remove_list
  {
    {"DICT", remove_dict},
    {"WORD", remove_word},
    {"TRNS", remove_trns}
  };

  func_t sub_find_list
  {
    {"WORD", find_word},
    {"TRNS", find_trns}
  };

  func_t sub_count_list
  {
    {"WORD", count_word},
    {"TRNS", count_trns}
  };

  func_t sub_save_list
  {
    {"FILE", save_file},
    {"OUT", save_out}
  };

  func_t sub_help_list
  {
    {"ADD", help_add},
    {"REMOVE", help_remove},
    {"FIND", help_find},
    {"COUNT", help_count},
    {"SAVE", help_save},
    {"DEFAULT", help_default}
  };
}
#endif
