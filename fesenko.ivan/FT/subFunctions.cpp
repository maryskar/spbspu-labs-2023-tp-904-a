#include "subFunctions.h"

void fesenko::print_word(const hash_t &hash, std::string word, std::ostream &out)
{
  auto list = hash.at(word);
  out << word;
  for (auto &it: list) {
    out << " " << it;
  }
  out << "\n";
}
