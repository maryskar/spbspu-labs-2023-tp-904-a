#include "subFunctions.h"
#include <cctype>

std::forward_list< std::string > fesenko::parse_line(const std::string line)
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
  list.reverse();
  return list;
}

void fesenko::print_word(const hash_t &hash, const std::string word, std::ostream &out)
{
  std::forward_list< size_t > list = hash.at(word);
  out << word;
  for (auto &it: list) {
    out << " " << it;
  }
  out << "\n";
}

void fesenko::insert_in_asc_order(std::forward_list< size_t > &list, size_t number)
{
  std::forward_list< size_t > copy = list;
  auto cur = list.before_begin();
  while (!copy.empty() && copy.front() < number) {
    copy.pop_front();
    cur++;
  }
  if (copy.front() == number) {
    return;
  }
  list.insert_after(cur, number);
}
