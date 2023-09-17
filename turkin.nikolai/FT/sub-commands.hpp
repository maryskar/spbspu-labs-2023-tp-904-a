#ifndef SUB_COMMANDS_HPP
#define SUB_COMMANDS_HPP

#include "data-types.hpp"

namespace turkin
{
  std::ostream & add_dict(base_t & base, std::istream & in, std::ostream & out);
  std::ostream & add_word(base_t & base, std::istream & in, std::ostream & out);
  std::ostream & add_trns(base_t & base, std::istream & in, std::ostream & out);
  std::ostream & remove_dict(base_t & base, std::istream & in, std::ostream & out);
  std::ostream & remove_word(base_t & base, std::istream & in, std::ostream & out);
  std::ostream & remove_trns(base_t & base, std::istream & in, std::ostream & out);
  std::ostream & find_word(base_t & base, std::istream & in, std::ostream & out);
  std::ostream & find_trns(base_t & base, std::istream & in, std::ostream & out);
  std::ostream & count_word(base_t & base, std::istream & in, std::ostream & out);
  std::ostream & count_trns(base_t & base, std::istream & in, std::ostream & out);
  std::ostream & save_file(base_t & base, std::istream & in, std::ostream & out);
  std::ostream & save_out(base_t & base, std::istream &, std::ostream & out);
  std::ostream & help_add(base_t &, std::istream &, std::ostream & out);
  std::ostream & help_remove(base_t &, std::istream &, std::ostream & out);
  std::ostream & help_find(base_t &, std::istream &, std::ostream & out);
  std::ostream & help_count(base_t &, std::istream &, std::ostream & out);
  std::ostream & help_save(base_t &, std::istream &, std::ostream & out);
  std::ostream & help_default(base_t &, std::istream &, std::ostream & out);
}

#endif
