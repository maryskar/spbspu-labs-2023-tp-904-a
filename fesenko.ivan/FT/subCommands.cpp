#include "subCommands.h"
#include <string>
#include <cctype>
#include <fstream>
#include <stdexcept>

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
      if (isalnum(c)) {
        if (isupper(c)) {
          c = tolower(c);
        }
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

std::ostream &fesenko::print_word_cmd(const data_t &data, std::istream &in, std::ostream &out)
{
  std::string dict_name = "";
  std::string word = "";
  in >> dict_name >> word;
  if (!in) {
    throw std::invalid_argument("Wrong input");
  }
  auto list = data.at(dict_name).at(word);
  out << word;
  for (auto &it: list) {
    out << " " << it;
  }
  return out << "\n";
}
