#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

#include <map>
#include <string>
#include <istream>
#include <ostream>
#include <utility>

namespace turkin
{
  using dict_t = std::map< std::string, std::string >;
  using word_it_t = dict_t::iterator;
  using word_pair_t = std::pair< std::string, std::string >;
  using base_t = std::map< std::string, dict_t >;
  using func_t = std::map< std::string, std::ostream & (*)(base_t &, std::istream &, std::ostream &) >;

  std::ostream & operator<<(std::ostream & out, const word_it_t & word);
  std::ostream & operator<<(std::ostream & out, const word_pair_t & word);
}

#endif
