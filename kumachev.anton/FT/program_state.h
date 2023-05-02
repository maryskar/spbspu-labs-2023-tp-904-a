#ifndef FT_PROGRAM_STATE_H
#define FT_PROGRAM_STATE_H

#include <string>
#include "english_russian_dictionary.h"

namespace kumachev {
  struct State {
    std::map< std::string, EnglishRussianDictionary< std::map< std::string, std::vector< std::string > > > > dicts_;
  };
}

#endif //FT_PROGRAM_STATE_H
