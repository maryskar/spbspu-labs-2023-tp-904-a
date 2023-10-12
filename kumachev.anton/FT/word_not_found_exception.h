#ifndef FT_WORD_NOT_FOUND_EXCEPTION_H
#define FT_WORD_NOT_FOUND_EXCEPTION_H

#include <stdexcept>

namespace kumachev {
  struct WordNotFound: std::runtime_error {
  public:
    WordNotFound(): std::runtime_error("Word not found")
    {}
  };
}

#endif //FT_WORD_NOT_FOUND_EXCEPTION_H
