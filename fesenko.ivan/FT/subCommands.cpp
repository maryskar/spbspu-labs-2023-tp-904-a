#include "subCommands.h"
#include <string>
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
  hash_t dict = data.at(dict_name);
  size_t counter = 0;
  std::string line = "";
  std::forward_list< std::string > word_list;
  while (std::getline(fin, line)) {
    counter++;
    word_list = parse_line(line);
    std::string word = "";
    while (!word_list.empty()) {
      word = word_list.front();
      word_list.pop_front();
      if (dict.find(word) == dict.end()) {
        std::forward_list< size_t > numbers;
        dict.insert(std::make_pair(word, numbers));
      }
      insert_in_asc_order(dict.at(word), counter);
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
  std::string line = "";
  std::getline(in, line);
  if (!in) {
    throw std::invalid_argument("Wrong input");
  }
  hash_t dict = data.at(dict_name);
  if (dict.find(word) == dict.end()) {
    std::forward_list< size_t > numbers;
    dict.insert(std::make_pair(word, numbers));
  }
  std::forward_list< std::string > num_list;
  num_list = parse_line(line);
  size_t number = 0;
  while (!num_list.empty()) {
    number = stoull(num_list.front());
    num_list.pop_front();
    insert_in_asc_order(dict.at(word), number);
  }
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
