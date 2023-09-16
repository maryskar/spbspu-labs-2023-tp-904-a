#ifndef FT_DICTIONARY_IO_H
#define FT_DICTIONARY_IO_H

#include <iosfwd>
#include "program_state.h"

namespace kumachev {
  std::istream &operator>>(std::istream &istream, er_dictionary &dict);
  std::ostream &operator<<(std::ostream &istream, er_dictionary &dict);
}

#endif
