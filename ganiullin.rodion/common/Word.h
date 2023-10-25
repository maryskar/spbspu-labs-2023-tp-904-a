#ifndef WORD_H
#define WORD_H

#include <functional>
#include <iosfwd>
#include <string>

namespace ganiullin {
  class Word {
  public:
    Word(const std::string& str);
    friend std::istream& operator>>(std::istream& in, Word& word);
    friend std::ostream& operator<<(std::ostream& out, const Word& word);
    friend bool operator<(const Word& lhs, const Word& rhs);
    friend bool operator==(const Word& lhs, const Word& rhs);
    const std::string& get() const;
    bool empty() const;

  private:
    std::string str_;
  };
  std::istream& operator>>(std::istream& in, Word& word);
  std::ostream& operator<<(std::ostream& out, const Word& word);
  bool operator<(const Word& lhs, const Word& rhs);
  bool operator==(const Word& lhs, const Word& rhs);
}
namespace std {
  template <> struct hash< ganiullin::Word > {
    size_t operator()(const ganiullin::Word& word) const;
  };
}
#endif
