#include "data-types.hpp"

std::ostream & turkin::operator<<(std::ostream & out, const word_it_t & word)
{
  return out << "WORD: " << word->first << "\tTRNS: " << word->second << "\n";
}

std::ostream & turkin::operator<<(std::ostream & out, const word_pair_t & word)
{
  return out << "WORD: " << word.first << "\tTRNS: " << word.second << "\n";
}
