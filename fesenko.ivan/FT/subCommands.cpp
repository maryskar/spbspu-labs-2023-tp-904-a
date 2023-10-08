#include "subCommands.h"
#include <string>
#include <cctype>
#include <fstream>
#include <stdexcept>
#include "subFunctions.h"

void fesenko::read_file_cmd(data_t &data, std::istream &in)
{
  std::string dict_name = "";
  std::string file_name = "";
  in >> dict_name >> file_name;
  if (!in) {
    throw std::invalid_argument("Wrong input");
  }
  std::ifstream fin(file_name);
  if (!fin.is_open()) {
    throw std::invalid_argument("Can`t open the file");
  }
  size_t counter = 0;
  std::string line = "";
  while (std::getline(fin, line)) {
    counter++;
    std::string word = "";
    for (size_t i = 0; i < line.size(); i++) {
      char c = line[i];
      if (std::isalnum(c)) {
        c = std::tolower(c);
        word += c;
      } else if (!word.empty()){
        data.at(dict_name).insert(std::make_pair(word, counter));
        word = "";
      }
    }
    if (!word.empty()){
      data.at(dict_name).insert(std::make_pair(word, counter));
      word = "";
    }
  }
}

void fesenko::delete_dict_cmd(data_t &data, std::istream &in)
{
  std::string dict_name = "";
  in >> dict_name;
  if (!in) {
    throw std::invalid_argument("Wrong input");
  }
  data.erase(dict_name);
}

void fesenko::delete_word_cmd(data_t &data, std::istream &in)
{
  std::string dict_name = "";
  std::string word = "";
  in >> dict_name >> word;
  if (!in) {
    throw std::invalid_argument("Wrong input");
  }
  data.at(dict_name).erase(word);
}

void fesenko::rename_cmd(data_t &data, std::istream &in)
{
  std::string dict_name = "";
  std::string new_dict_name = "";
  in >> dict_name >> new_dict_name;
  if (!in) {
    throw std::invalid_argument("Wrong input");
  }
  hash_t temp = data.at(dict_name);
  data.erase(dict_name);
  data.insert(std::make_pair(new_dict_name, temp));
}

void fesenko::insert_cmd(data_t &data, std::istream &in)
{
  std::string dict_name = "";
  std::string word = "";
  in >> dict_name >> word;
  if (!in) {
    throw std::invalid_argument("Wrong input");
  }
  std::forward_list< size_t > list;
  std::string line = "";
  std::getline(in, line);
  std::string number = "";
  for (size_t i = 0; i < line.size(); i++) {
    if (std::isdigit(line[i])) {
      number += line[i];
    } else if (!number.empty()) {
      list.push_front(std::stoull(number));
      number = "";
    }
  }
  list.sort();
  data.at(dict_name).insert(std::make_pair(word, list));
}

std::ostream &fesenko::print_word_cmd(const data_t &data, std::istream &in, std::ostream &out)
{
  std::string dict_name = "";
  std::string word = "";
  in >> dict_name >> word;
  if (!in) {
    throw std::invalid_argument("Wrong input");
  }
  hash_t hash = data.at(dict_name);
  print_word(hash, word, out);
  return out;
}

std::ostream &fesenko::print_dict_cmd(const data_t &data, std::istream &in, std::ostream &out)
{
  std::string dict_name = "";
  in >> dict_name;
  if (!in) {
    throw std::invalid_argument("Wrong input");
  }
  hash_t hash = data.at(dict_name);
  for (auto &it: hash) {
    print_word(hash, it.first, out);
  }
  return out;
}
