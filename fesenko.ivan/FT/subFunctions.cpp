#include "subFunctions.h"
#include <cctype>

std::forward_list< std::string > fesenko::parse_line(std::string line)
{
  std::forward_list< std::string > list;
  if (line.empty()) {
    return list;
  }
  std::string word = "";
  for (size_t i = 0; i < line.size(); i++) {
    char c = line[i];
    if (std::isalnum(c)) {
      word += std::tolower(c);;
    } else if (!word.empty()){
      list.push_front(word);
      word = "";
    }
  }
  if (!word.empty()){
    list.push_front(word);
    word = "";
  }
  return list;
}

void fesenko::print_word(const hash_t &hash, std::string word, std::ostream &out)
{
  auto list = hash.at(word);
  out << word;
  for (auto &it: list) {
    out << " " << it;
  }
  out << "\n";
}
