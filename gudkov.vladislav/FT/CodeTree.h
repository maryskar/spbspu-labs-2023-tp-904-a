#ifndef CODE_TREE_H
#define CODE_TREE_H

#include <memory>
#include "CharacterFrequency.h"
#include "SymbolCodes.h"
#include "BinaryCode.h"
#include "Text.h"

namespace gudkov
{
  class CodeTree
  {
  public:
    ~CodeTree() = default;

    CodeTree(const CodeTree &) = delete;
    CodeTree &operator=(const CodeTree &) = delete;

    CodeTree(CodeTree &&) = default;
    CodeTree &operator=(CodeTree &&) = default;

    CodeTree();
    CodeTree(const SymbolCodes &symbolCodes);

    void clear();

    void fill(const CharacterFrequency &alphabetFrequency);
    SymbolCodes createCode() const;

    Text decode(const BinaryCode &code) const;

    void insert(char symbol, const std::string &code);

  private:
    struct Node
    {
      char data_;
      std::shared_ptr< Node > left_;
      std::shared_ptr< Node > right_;
      Node(char value);
    };

    static const char dummyChar_ = '\a';
    std::shared_ptr< Node > root_;

    static void fillRecursive(std::shared_ptr< Node > root, const CharacterFrequency &alphabetFrequency);
    static void createCodeRecursive(std::shared_ptr< Node > root, BinaryCode &word, SymbolCodes &codeWords);

    char decodeNextSymbol(const BinaryCode &code, size_t &index) const;

    static void print_recursive(std::ostream &out, std::vector< bool > &code, std::shared_ptr< Node > root_, size_t level);

    friend std::ostream &operator<<(std::ostream &out, const CodeTree &departure);
  };
}
#endif
