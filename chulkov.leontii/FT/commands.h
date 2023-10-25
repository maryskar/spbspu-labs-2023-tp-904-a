#ifndef COMMANDS_H
#define COMMANDS_H
#include "dict.h"
#include <iostream>
#include <vector>

namespace chulkov {
  using cnstIter = std::vector< Dict >::const_iterator;
  void insert(std::istream &input, std::ostream &output, std::vector< Dict > &dicts);
  void remove(std::istream &input, std::ostream &output, std::vector< Dict > &dicts);
  void search(std::istream &input, std::ostream &output, std::vector< Dict > &dicts);
  void printMaxCountWords(std::istream &input, std::ostream &output, std::vector< Dict > &dicts);
  void print(std::istream &input, std::ostream &output, std::vector< Dict > &dicts);
  auto isFound(const std::vector< Dict > &dicts, cnstStr &name);
  auto isFound(std::vector< Dict > &dicts, cnstStr &name);
  void save(std::istream &input, std::ostream &output, std::vector< Dict > &dicts);
  void load(std::istream &input, std::ostream &output, std::vector< Dict > &dicts);
  void getSize(std::istream &input, std::ostream &output, std::vector< Dict > &dicts);
  void count(std::istream &input, std::ostream &output, std::vector< Dict > &dicts);
  void clear(std::istream &input, std::ostream &output, std::vector< Dict > &dicts);
  void getNamesAndDoCommand(std::istream &input, std::vector< Dict > &dicts, cnstStr &cmd);
  void intersect(std::istream &input, std::ostream &output, std::vector< Dict > &dicts);
  void intersectionCommand(std::vector< Dict > &dicts, cnstStr &name, cnstIter it1, cnstIter it2, cnstStr &cmd, char c);
  void unionData(std::istream &input, std::ostream &output, std::vector< Dict > &dicts);
  std::ostream &operator<<(std::ostream &os, const Dict &dict);
  std::istream &operator>>(std::istream &is, Dict &dict);
}
#endif
