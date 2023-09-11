#ifndef FT_PROGRAM_STATE_H
#define FT_PROGRAM_STATE_H

#include <string>
#include <map>
#include <vector>

namespace kumachev {
  using er_dictionary = std::map< std::string, std::vector< std::string > >;
  using dict_map = std::map< std::string, er_dictionary >;

  struct State {
     dict_map dicts;
  };
}

#endif //FT_PROGRAM_STATE_H
