#include "dictionary.hpp"

Dictionary::Dictionary():
  dict_()
{}
void Dictionary::insert(const std::string& word)
{
  ++dict_[word];
}
