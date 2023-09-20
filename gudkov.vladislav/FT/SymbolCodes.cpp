#include "SymbolCodes.h"

gudkov::SymbolCodes::iterator gudkov::SymbolCodes::begin() const
{
  return data_.begin();
}

gudkov::SymbolCodes::iterator gudkov::SymbolCodes::end() const
{
  return data_.end();
}

void gudkov::SymbolCodes::pushBack(char symbol, const BinaryCode &info)
{
  data_.insert(std::pair< char, BinaryCode >(symbol, info));
}

gudkov::BinaryCode gudkov::SymbolCodes::encode(const Text &text) const
{
  BinaryCode code;

  for (const Line &line : text)
  {
    for (char symbol : line)
    {
      SymbolCodes::iterator codeWord = data_.find(symbol);

      if (codeWord == data_.end())
      {
        throw std::runtime_error("Wrong code tree: symbol is missing.\n");
      }

      for (bool bit : codeWord->second)
      {
        code.pushBack(bit);
      }
    }
  }

  return code;
}

std::istream &gudkov::operator>>(std::istream &in, SymbolCodes &destination)
{
  while (!in.eof())
  {
    const char symbol = in.get();

    if (in.eof())
    {
      break;
    }

    if (!in)
    {
      throw std::runtime_error("Wrong bit code: symbol is missing.\n");
    }

    in.get();

    if (!in)
    {
      throw std::runtime_error("Wrong bit code: space after symbol is missing.\n");
    }

    char bit = ' ';
    BinaryCode code;

    while (!in.eof() && (bit = in.get()) != '\n')
    {
      if (!in)
      {
        throw std::runtime_error("Wrong bit code: 0 / 1 expected.\n");
      }

      if (bit == '0')
      {
        code.pushBack(0);
      }
      else if (bit == '1')
      {
        code.pushBack(1);
      }
      else
      {
        throw std::runtime_error("Wrong bit: 0 / 1 expected.\n");
      }
    }

    if (code.size() == 0)
    {
      throw std::runtime_error("Wrong bit code: empty sequence.\n");
    }

    destination.data_[symbol] = code;
  }

  return in;
}

std::ostream &gudkov::operator<<(std::ostream &out, const SymbolCodes &departure)
{
  for (const auto &element : departure.data_)
  {
    out << element.first << " ";
    for (size_t i = 0; i < element.second.size(); ++i)
    {
      out << element.second[i];
    }
    out << std::endl;
  }

  return out;
}
