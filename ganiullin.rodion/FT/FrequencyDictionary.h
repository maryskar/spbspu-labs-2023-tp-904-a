#ifndef FREQUENCY_DICTIONARY_H
#define FREQUENCY_DICTIONARY_H
#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

namespace ganiullin {
  using NodeType = std::pair< std::string, size_t >;
  using FreqDict = std::unordered_map< std::string, size_t >;
  using VectorDict = std::vector< std::pair< std::string, size_t > >;
  using SubCommand = size_t (*)(const size_t&, const size_t&);

  FreqDict merge(const FreqDict& lhs, const FreqDict& rhs,
      const SubCommand getNewValue);
  FreqDict getIntersect(const FreqDict& lhs, const FreqDict& rhs,
      const SubCommand getNewValue);
  FreqDict getDifference(const FreqDict& lhs, const FreqDict& rhs);
  template < class T >
  VectorDict getSorted(const FreqDict& src, const T& predicate);
  std::ostream& print(std::ostream& out, const FreqDict& src);
  std::ostream& printRareElems(std::ostream& out, const FreqDict& src,
      size_t num);
  std::ostream& printCommonElems(std::ostream& out, const FreqDict& src,
      size_t num);
  std::istream& readText(std::istream& in, FreqDict& src);
  std::ifstream& loadDict(std::ifstream& in, FreqDict& src);
  std::ofstream& saveDict(std::ofstream& out, const FreqDict& src);
}
#endif
