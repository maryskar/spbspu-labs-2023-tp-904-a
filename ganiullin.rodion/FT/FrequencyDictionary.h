#ifndef FREQUENCY_DICTIONARY_H
#define FREQUENCY_DICTIONARY_H

#include <functional>
#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

#include "Word.h"

namespace ganiullin {
  using SubComm = std::function< size_t(const size_t&, const size_t&) >;
  using VectorDict = std::vector< std::pair< Word, size_t > >;
  class FreqDict {
  public:
    bool contains(const Word& key) const;
    const size_t& at(const Word& key) const;

    FreqDict merge(const FreqDict& other, const SubComm func) const;
    FreqDict intersect(const FreqDict& other, const SubComm func) const;
    FreqDict diff(const FreqDict& other) const;
    std::ostream& printRareElems(std::ostream& out, size_t num) const;
    std::ostream& printCommonElems(std::ostream& out, size_t num) const;
    std::istream& readText(std::istream& in);

    friend std::istream& operator>>(std::istream& in, FreqDict& src);
    friend std::ostream& operator<<(std::ostream& out, const FreqDict& src);

  private:
    std::unordered_map< Word, size_t > map_;
    template < class T > VectorDict getSorted(const T& predicate) const;
    static std::ostream& printSomeElems(
        std::ostream& out, const VectorDict& src, size_t num);
  };
  std::istream& operator>>(std::istream& in, FreqDict& src);
  std::ostream& operator<<(std::ostream& out, const FreqDict& src);
}
#endif
