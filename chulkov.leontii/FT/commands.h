#ifndef COMMANDS_H
#define COMMANDS_H
#include <iostream>
#include <vector>
#include "dict.h"

namespace chulkov {

  void insert(std::istream& input, std::vector< Dict >& dicts);
  void remove(std::istream& input, std::vector< Dict >& dicts);
  void search(std::istream& input, std::ostream& output, const std::vector< Dict >& dicts);
  void printMaxCountWords(std::istream& input, std::ostream& output, const std::vector< Dict >& dicts);
  void print(std::istream& input, std::ostream& output, const std::vector< Dict >& dicts);
  auto isFound(const std::vector< Dict >& dicts, cnstStr& name);
  auto isFound(std::vector< Dict >& dicts, cnstStr& name);
  void save(std::istream& input, const std::string &path);
  void load(const std::string& dataset, const std::string &path);
  void getSize(const std::string &dataset);
  void count(std::istream& input, std::ostream& output, const std::vector< Dict >& dicts);
  void clear(std::istream& input, std::vector< Dict >& dicts);
  void getNamesAndDoCommand(std::istream& input, std::vector< Dict >& dicts, cnstStr& cmd);
  void intersect(std::istream& input, std::vector< Dict >& dicts);
  void intersectionCommand(std::vector< Dict >& dicts, cnstStr& name, std::vector< Dict >::const_iterator it1, std::vector< Dict >::const_iterator it2, cnstStr& cmd, char c);
  void unionData(const std::string& newDataset, const std::vector<std::string>& datasets, std::vector<Dict>& dicts);
}
#endif
