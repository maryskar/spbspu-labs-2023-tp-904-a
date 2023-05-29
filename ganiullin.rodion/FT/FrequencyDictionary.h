#ifndef FREQUENCY_DICTIONARY_H
#define FREQUENCY_DICTIONARY_H
#include <iosfwd>
#include <string>
#include <unordered_map>

namespace ganiullin {
  struct FrequencyDictionary {
    std::unordered_map< std::string, size_t > map;
  };
  std::istream& operator>>(std::istream& in, FrequencyDictionary&);
  std::ostream& operator<<(std::ostream& out, FrequencyDictionary&);
  void unite(const FrequencyDictionary&, const FrequencyDictionary&, const FrequencyDictionary&, class func);
  void intersect(const FrequencyDictionary&, const FrequencyDictionary&, const FrequencyDictionary&, class func);
  void diff(const FrequencyDictionary&, const FrequencyDictionary&, const FrequencyDictionary&, class func);
  void print(const FrequencyDictionary&, class predicate);

  struct WordI {
    std::string&& dest;
  };
  struct WordO {
    std::string&& dest;
  };

}
#endif
