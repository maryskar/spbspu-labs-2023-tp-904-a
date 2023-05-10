#ifndef FT_PROGRAM_STATE_H
#define FT_PROGRAM_STATE_H

#include <string>
#include "english_russian_dictionary.h"

namespace kumachev {
  struct State {
    std::map< std::string, EnglishRussianDictionary > dicts;
  };
}

#endif //FT_PROGRAM_STATE_H
