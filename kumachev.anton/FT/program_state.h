#ifndef FT_PROGRAM_STATE_H
#define FT_PROGRAM_STATE_H

#include <string>
#include <map>
#include <vector>

namespace kumachev {
  using er_dictionary = std::map< std::string, std::vector< std::string > >;

  struct State {
    std::map< std::string, er_dictionary > dicts;
  };
}

#endif //FT_PROGRAM_STATE_H
