#include "subFunctions.h"
#include <cctype>
#include <string>

std::string fesenko::get_cmd_word(std::string &line)
{
  if (line.empty()) {
    throw std::invalid_argument("Wrong input");
  }
  std::string word = "";
  while (!line.empty()) {
    char c = line[0];
    line.erase(0, 1);
    if (!isspace(c)) {
      word += c;
    } else if (!word.empty()){
      break;
    }
  }
  if (word.empty()) {
    throw std::invalid_argument("Wrong input");
  }
  while (!line.empty() && isspace(line[0])) {
    line.erase(0, 1);
  }
  return word;
}

std::forward_list< std::string > fesenko::parse_text_line(const std::string line)
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
  list_t list = hash.at(word);
  out << word;
  for (auto &it: list) {
    out << " " << it;
  }
  out << "\n";
}

void fesenko::insert_in_asc_order(list_t &list, size_t number)
{
  list_t copy = list;
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

void fesenko::make_complementation(data_t &data, std::string new_dict_name, std::string dict_name1, std::string dict_name2)
{
  data[new_dict_name] = data.at(dict_name1);
  if (data.at(dict_name1).empty() || dict_name1.compare(dict_name2) == 0) {
    data.at(new_dict_name).clear();
    return;
  }
  if (data.at(dict_name2).empty()) {
    return;
  }
  hash_t new_dict = data.at(new_dict_name);
  hash_t dict2 = data.at(dict_name2);
  for (auto &it: new_dict) {
    if (dict2.find(it.first) != dict2.end()) {
      list_t new_list = it.second;
      list_t list2 = dict2.at(it.first);
      make_complementation(new_list, list2);
      if (new_list.empty()) {
        new_dict.erase(it.first);
      }
    }
  }
}

void fesenko::make_complementation(list_t &list1, const list_t &list2)
{
  list_t list1_cp = list1;
  list_t list2_cp = list2;
  while (!list1_cp.empty() && !list2_cp.empty()) {
    if (list1_cp.front() == list2_cp.front()) {
      list1.remove(list1_cp.front());
      list1_cp.pop_front();
      list2_cp.pop_front();
    } else if (list1_cp.front() < list2_cp.front()) {
      list1_cp.pop_front();
    } else {
      list2_cp.pop_front();
    }
  }
}
