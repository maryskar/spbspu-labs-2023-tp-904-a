#include "commands.h"

std::string cutS(std::string& line)
{
  std::string res = "";
  std::size_t pos = line.find(' ');

  if (pos != std::string::npos)
  {
    res = line.substr(0, pos);
    line.erase(0, pos + 1);

    return res;
  }
  else if (line != "")
  {
    res = line;
    line = "";

    return res;
  }
  else
  {
    throw std::invalid_argument("incorrect args");
  }
}

void dmitriev::addBook(library& lib, std::istream& inp)
{
  std::string line = "";
  std::getline(inp, line);

  std::string dirName = cutS(line);

  dmitriev::Book newBook{cutS(line), cutS(line), cutS(line), cutS(line), std::stol(cutS(line))};
  lib.at(dirName)[newBook.key] = newBook;
}
