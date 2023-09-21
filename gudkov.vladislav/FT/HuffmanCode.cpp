#include "HuffmanCode.h"

gudkov::HuffmanCode::HuffmanCode(const CharacterFrequency &characterFrequency)
{
  if (characterFrequency.isEmpty())
  {
    throw std::runtime_error("Characters for coding is missing.\n");
  }

  codeTree_.fill(characterFrequency);
  codeSymbols_ = codeTree_.createCode();
}

gudkov::HuffmanCode::HuffmanCode(const Text &text):
  HuffmanCode(CharacterFrequency(text))
{

}

gudkov::HuffmanCode::HuffmanCode(const SymbolCodes &symbolsCodes):
  codeSymbols_(symbolsCodes), codeTree_(codeSymbols_)
{

}

const gudkov::SymbolCodes &gudkov::HuffmanCode::getCodeSymbols() const
{
  return codeSymbols_;
}

const gudkov::CodeTree &gudkov::HuffmanCode::getCodeTree() const
{
  return codeTree_;
}

gudkov::BinaryCode gudkov::HuffmanCode::encode(const Text &textToEncode) const
{
  return codeSymbols_.encode(textToEncode);
}

gudkov::Text gudkov::HuffmanCode::decode(const BinaryCode &textToDecode) const
{
  return codeTree_.decode(textToDecode);
}
