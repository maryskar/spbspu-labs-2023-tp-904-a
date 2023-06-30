#ifndef FREQUENCY_DICTIONARY_H
#define FREQUENCY_DICTIONARY_H
#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

namespace ganiullin {
  using NodeType = std::pair< std::string, size_t >;
  using Dict = std::unordered_map< std::string, size_t >;
  using VectorDict = std::vector< std::pair< std::string, size_t > >;
  using SubComm = size_t (*)(const size_t&, const size_t&);
  using OutS = std::ostream;
  using InS = std::istream;

  Dict merge(const Dict& lhs, const Dict& rhs, const SubComm getNewValue);
  Dict getIntersect(const Dict& lhs, const Dict& rhs,
      const SubComm getNewValue);
  Dict getDifference(const Dict& lhs, const Dict& rhs);
  template < class T >
  VectorDict getSorted(const Dict& src, const T& predicate);
  OutS& print(OutS& out, const Dict& src);
  OutS& printSomeElems(OutS& out, const VectorDict& src, size_t num);
  OutS& printRareElems(OutS& out, const Dict& src, size_t num);
  OutS& printCommonElems(OutS& out, const Dict& src, size_t num);
  InS& readText(InS& in, Dict& src);
  std::ifstream& loadDict(std::ifstream& in, Dict& src);
  std::ofstream& saveDict(std::ofstream& out, const Dict& src);
}
#endif
