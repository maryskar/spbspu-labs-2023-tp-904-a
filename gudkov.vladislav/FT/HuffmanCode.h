#ifndef HUFFMAN_CODE_H
#define HUFFMAN_CODE_H

#include "SymbolCodes.h"
#include "CharacterFrequency.h"
#include "CodeTree.h"
#include "BinaryCode.h"
#include "Text.h"

namespace gudkov
{
  class HuffmanCode
  {
  public:
    HuffmanCode() = default;
    ~HuffmanCode() = default;

    HuffmanCode(const HuffmanCode &other) = default;
    HuffmanCode &operator=(const HuffmanCode &other) = default;

    HuffmanCode(HuffmanCode &&other) = default;
    HuffmanCode &operator=(HuffmanCode &&other) = default;

    HuffmanCode(const Text &input);
    HuffmanCode(const CharacterFrequency &characterFrequency);
    HuffmanCode(const SymbolCodes &symbolsCodes);

    const SymbolCodes &getCodeSymbols() const;
    const CodeTree &getCodeTree() const;

    BinaryCode encode(const Text &textToEncode) const;
    Text decode(const BinaryCode &textToDecode) const;
  private:
    SymbolCodes codeSymbols_;
    CodeTree codeTree_;
  };
}
#endif
