#include "subFunctions.h"

std::ostream &fesenko::print_word(hash_t &hash, std::string word, std::ostream &out)
{
  auto list = hash.at(word);
  out << word;
  for (auto &it: list) {
    out << " " << it;
  }
  return out << "\n";
}
