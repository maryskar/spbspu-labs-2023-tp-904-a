#ifndef SUBFUNCTIONS_H
#define SUBFUNCTIONS_H
#include <unordered_map>
#include <forward_list>
#include <ostream>
namespace fesenko
{
  using hash_t = std::unordered_map< std::string, std::forward_list< size_t > >;
  std::forward_list< std::string > parse_line(std::string line);
  void print_word(const hash_t &hash, const std::string word, std::ostream &out);
  void insert_in_asc_order(std::forward_list< size_t > &list, size_t number);
}
#endif
