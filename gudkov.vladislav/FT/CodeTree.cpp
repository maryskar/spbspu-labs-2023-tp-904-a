#include "CodeTree.h"
#include <utility>

gudkov::CodeTree::Node::Node(char value):
  data_(value),
  left_(),
  right_()
{

}

gudkov::CodeTree::CodeTree():
  root_(new Node(dummyChar_))
{

}

gudkov::CodeTree::CodeTree(const SymbolCodes &codeSymbols):
  CodeTree()
{
  for (const auto &element : codeSymbols)
  {
    insert(element.first, element.second.toString());
  }
}

void gudkov::CodeTree::clear()
{
  root_->left_ = nullptr;
  root_->right_ = nullptr;
}

void gudkov::CodeTree::fillRecursive(std::shared_ptr< Node > root, const CharacterFrequency &alphabetFrequency)
{
  std::pair<CharacterFrequency, CharacterFrequency> parts;
  alphabetFrequency.splitTwoParts(parts);

  if (!parts.first.isEmpty())
  {
    if (parts.first.size() == 1)
    {
      root->left_ = std::shared_ptr< Node >(new Node(parts.first.getFirstChar()));
    }
    else
    {
      root->left_ = std::shared_ptr< Node >(new Node(dummyChar_));
      fillRecursive(root->left_, parts.first);
    }
  }

  if (!parts.second.isEmpty())
  {
    if (parts.second.size() == 1)
    {
      root->right_ = std::shared_ptr< Node >(new Node(parts.second.getFirstChar()));
    }
    else
    {
      root->right_ = std::shared_ptr< Node >(new Node(dummyChar_));
      fillRecursive(root->right_, parts.second);
    }
  }
}

void gudkov::CodeTree::fill(const CharacterFrequency &alphabetFrequency)
{
  fillRecursive(root_, alphabetFrequency);
}

void gudkov::CodeTree::createCodeRecursive(std::shared_ptr< Node > root, BinaryCode &word, SymbolCodes &codeWords)
{
  if (root->data_ != dummyChar_)
  {
    codeWords.pushBack(root->data_, word);
    return;
  }

  word.pushBack(false);
  createCodeRecursive(root->left_, word, codeWords);
  word.popBack();

  word.pushBack(true);
  createCodeRecursive(root->right_, word, codeWords);
  word.popBack();
}

gudkov::SymbolCodes gudkov::CodeTree::createCode() const
{
  SymbolCodes codeWords;
  BinaryCode word;

  createCodeRecursive(root_, word, codeWords);

  return codeWords;
}

char gudkov::CodeTree::decodeNextSymbol(const BinaryCode &code, size_t &i) const
{
  std::shared_ptr< Node > temp = root_;

  while (i < code.size())
  {
    if (code[i] == true)
    {
      temp = temp->right_;
    }
    else
    {
      temp = temp->left_;
    }

    ++i;

    if (temp == nullptr)
    {
      throw std::runtime_error("Wrong code tree: wrong code of symbol (too long code).\n");
    }

    if (temp->data_ != '\a')
    {
      return temp->data_;
    }
  }

  throw std::runtime_error("Wrong code tree: wrong code of symbol (too short code).\n");
}

gudkov::Text gudkov::CodeTree::decode(const BinaryCode &code) const
{
  Text text;

  Line line;
  size_t index = 0;

  while (index < code.size())
  {
    char symbol = decodeNextSymbol(code, index);
    line.pushBack(symbol);
    if (symbol == '\n')
    {
      text.pushBack(line);
      line.clear();
    }
  }

  if (!line.isEmpty())
  {
    text.pushBack(line);
  }

  return text;
}

void gudkov::CodeTree::insert(char symbol, const std::string &code)
{
  std::shared_ptr< Node > temp = root_;

  for (char character : code)
  {
    if (character == '1')
    {
      if (temp->right_ == nullptr)
      {
        temp->right_ = std::shared_ptr< Node >(new Node(dummyChar_));
      }
      temp = temp->right_;
    }
    else if (character == '0')
    {
      if (temp->left_ == nullptr)
      {
        temp->left_ = std::shared_ptr< Node >(new Node(dummyChar_));
      }
      temp = temp->left_;
    }
    else
    {
      throw std::runtime_error("Wrong symbol code: invalid symbol [0 / 1 expected].\n");
    }
  }

  temp->data_ = symbol;
}

void gudkov::CodeTree::print_recursive(std::ostream &out, std::vector< bool > &code, std::shared_ptr< Node > root, size_t level)
{
  if (root == nullptr)
  {
    return;
  }

  code.push_back(true);
  print_recursive(out, code, root->right_, level + 1);
  code.pop_back();

  for (size_t i = 0; i < level; ++i)
  {
    out << "    ";
  }

  {
    out << "'" << (root->data_ != '\a' ? root->data_ : ' ') << "'";

    out << "(";
    for (bool elem : code)
    {
      out << elem;
    }
    out << ")";
  }

  out << std::endl;

  code.push_back(false);
  print_recursive(out, code, root->left_, level + 1);
  code.pop_back();
}

std::ostream &gudkov::operator<<(std::ostream &out, const CodeTree &departure)
{
  std::vector< bool > code;

  CodeTree::print_recursive(out, code, departure.root_, 0);

  return out;
}
