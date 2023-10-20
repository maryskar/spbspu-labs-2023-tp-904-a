#include "FrequencyDictionary.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>

#include "NodeIO.h"
#include "TypesIO.h"

using FreqDict = ganiullin::FreqDict;
using Dict = std::unordered_map< ganiullin::Word, size_t >;
using SubComm = ganiullin::SubComm;
using NodeType = std::pair< const ganiullin::Word, size_t >;
using VectorDict = ganiullin::VectorDict;
namespace {
  bool compareNodes(const NodeType& lhs, const NodeType& rhs)
  {
    if (lhs.second == rhs.second) {
      return lhs.first < rhs.first;
    }
    return lhs.second > rhs.second;
  }
}
bool FreqDict::contains(const Word& key) const
{
  return map_.find(key) != std::end(map_);
}
const size_t& FreqDict::at(const Word& key) const
{
  return map_.at(key);
}
FreqDict FreqDict::merge(const FreqDict& other, const SubComm func) const
{
  FreqDict res;
  res.map_.reserve(std::max(map_.size(), other.map_.size()));

  for (const NodeType& elem : map_) {
    size_t valueToInsert = 0;
    try {
      valueToInsert = func(elem.second, other.map_.at(elem.first));
    } catch (...) {
      valueToInsert = elem.second;
    }
    res.map_[elem.first] = valueToInsert;
  }
  for (const NodeType& elem : other.map_) {
    if (!res.contains(elem.first)) {
      res.map_[elem.first] = elem.second;
    }
  }
  return res;
}
FreqDict FreqDict::intersect(const FreqDict& other, const SubComm func) const
{
  FreqDict res;

  for (const NodeType& elem : map_) {
    if (other.contains(elem.first)) {
      size_t valueToInsert = func(elem.second, other.map_.at(elem.first));
      res.map_[elem.first] = valueToInsert;
    }
  }
  return res;
}
FreqDict FreqDict::diff(const FreqDict& other) const
{
  FreqDict res;

  for (const NodeType& elem : map_) {
    if (!other.contains(elem.first)) {
      res.map_[elem.first] = elem.second;
    }
  }
  for (const NodeType& elem : other.map_) {
    if (!contains(elem.first)) {
      res.map_[elem.first] = elem.second;
    }
  }
  return res;
}
template < class T > VectorDict FreqDict::getSorted(const T& predicate) const
{
  VectorDict res;
  res.reserve(map_.size());
  auto dictBeginIt = std::begin(map_);
  auto dictEndIt = std::end(map_);
  auto resInsertIt = std::back_inserter(res);
  std::copy(dictBeginIt, dictEndIt, resInsertIt);
  auto resBeginIt = std::begin(res);
  auto resEndIt = std::end(res);

  std::sort(resBeginIt, resEndIt, predicate);
  return res;
}
std::ostream& FreqDict::printSomeElems(
    std::ostream& out, const VectorDict& src, size_t num)
{
  num = std::min(num, src.size());
  auto beginIt = std::begin(src);
  auto outIt = std::ostream_iterator< ganiullin::VecNode >(out, "\n");

  std::copy_n(beginIt, num, outIt);
  return out;
}

std::ostream& FreqDict::printRareElems(std::ostream& out, size_t num) const
{
  using namespace std::placeholders;
  auto comp = std::bind(compareNodes, _2, _1);
  printSomeElems(out, getSorted(comp), num);
  return out;
}
std::ostream& FreqDict::printCommonElems(std::ostream& out, size_t num) const
{
  printSomeElems(out, getSorted(compareNodes), num);
  return out;
}
std::istream& FreqDict::readText(std::istream& in)
{
  while (!in.eof()) {
    Word word("");
    try {
      in >> word;
      if (!word.empty()) {
        map_[word] += 1;
      }
    } catch (const std::logic_error& e) {
    }
  }
  return in;
}
std::istream& ganiullin::operator>>(std::istream& in, FreqDict& src)
{
  while (!(in.peek() == '\n' || in.eof())) {
    Word word("");
    size_t val = 0;
    try {
      in >> word >> val;
    } catch (const std::logic_error& e) {
    }
    if (val != 0 && !word.empty()) {
      src.map_[word] = val;
    }
    if (!in) {
      in.clear();
    }
  }
  return in;
}
std::ostream& ganiullin::operator<<(std::ostream& out, const FreqDict& src)
{
  VectorDict dict = src.getSorted(compareNodes);
  auto beginIt = std::begin(dict);
  auto endIt = std::end(dict);
  auto outIt = std::ostream_iterator< ganiullin::VecNode >(out, " ");

  std::copy(beginIt, endIt, outIt);
  return out;
}
