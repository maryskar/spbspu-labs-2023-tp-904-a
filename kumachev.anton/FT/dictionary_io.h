#ifndef FT_DICTIONARY_IO_H
#define FT_DICTIONARY_IO_H

#include <iosfwd>
#include "program_state.h"

namespace kumachev {
  struct DictEntryIO {
    std::string english;
    std::vector< std::string > russian;
  };

  std::istream &operator>>(std::istream &istream, DictEntryIO &entry);
  std::istream &operator>>(std::istream &istream, er_dictionary &dict);
  std::ostream &operator<<(std::ostream &ostream, const DictEntryIO &entry);
  std::ostream &operator<<(std::ostream &ostream, const er_dictionary &dict);
}

#endif
