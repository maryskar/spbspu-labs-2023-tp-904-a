#ifndef CODE_WORDS_H
#define CODE_WORDS_H

#include <iostream>
#include <map>
#include "BinaryCode.h"
#include "Text.h"

namespace gudkov
{
  class SymbolCodes
  {
  public:
    using iterator = std::map< char, BinaryCode >::const_iterator;

    SymbolCodes() = default;
    ~SymbolCodes() = default;

    SymbolCodes(const SymbolCodes &) = default;
    SymbolCodes &operator=(const SymbolCodes &) = default;

    SymbolCodes(SymbolCodes &&) = default;
    SymbolCodes &operator=(SymbolCodes &&) = default;

    iterator begin() const;
    iterator end() const;

    void pushBack(char symbol, const BinaryCode &info);

    BinaryCode encode(const Text &text) const;

  private:
    std::map< char, BinaryCode > data_;

    friend std::istream &operator>>(std::istream &in, SymbolCodes &destination);
    friend std::ostream &operator<<(std::ostream &out, const SymbolCodes &departure);
  };
}
#endif
