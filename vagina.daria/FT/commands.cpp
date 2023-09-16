#include "commands.hpp"


void createSet(Dictionary& dict, std::istream& in)
{
  std::string filename = "";
  in >> filename;
  std::ifstream file(filename);
  std::string word;

  while (file >> word) 
  {
    word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
    std::transform(word.begin(), word.end(), word.begin(), tolower);
    dict.insert(word);
  }
}
void threeMostPopular(const Dictionary& dict, std::ostream& out)
{
  std::vector< std::pair <std::string, size_t> > sorted_word_count(dict.dict_.begin(), dict.dict_.end());
  std::sort(sorted_word_count.begin(), sorted_word_count.end(), [](const auto& p1, const auto& p2) { return p1.second > p2.second; });
  std::vector< std::pair <std::string, size_t> > first_three_keys;
  std::copy_n(sorted_word_count.begin(), 3, std::back_inserter(first_three_keys));
  for (const auto& p : first_three_keys)
  {
    out << p.first << ": " << p.second << std::endl;
  }
}

void print(const Dictionary& dict, std::ostream& out)
{
  for (const auto& pair : dict.dict_) {
    out << pair.first << ": " << pair.second << '\n';
  }
}
