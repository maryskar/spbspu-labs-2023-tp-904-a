#include "commands.h"
#include <forward_list>

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

size_t hammingDistance(const std::string& lhs, const std::string& rhs)
{
  size_t distance = 0;
  size_t length = std::min(lhs.length(), rhs.length());

  for (size_t i = 0; i < length; i++)
  {
    if (lhs[i] != rhs[i])
    {
      distance++;
    }
  }

  distance += std::abs(static_cast< int >(lhs.length() - rhs.length()));

  return distance;
}

std::forward_list< dmitriev::Book > findBooks(const dmitriev::library& lib,
  const std::string& dir,
  const std::string& query,
  const std::string& parameter,
  size_t k)
{
  std::forward_list< dmitriev::Book > result;
  const dmitriev::directory& books = lib.at(dir);

  typename dmitriev::directory::const_iterator it = books.cbegin();
  for (; it != books.cend(); it++)
  {
    bool p1 = (parameter == "year" && std::to_string(it->second.year) == query);
    bool p2 = (parameter == "isbn" && it->second.isbn == query);

    std::string rhsStr = parameter == "title" ? it->second.title : it->second.author;
    size_t distance = hammingDistance(query, rhsStr);
    bool p3 = (parameter == "title" || parameter == "author") && distance <= k;

    if (p1 || p2 || p3)
    {
      result.push_front(it->second);
    }
  }

  return result;
}

void dmitriev::deleteBook(library& lib, std::istream& inp)
{
  std::string line = "";
  std::getline(inp, line);

  std::string dirName = cutS(line);
  std::string query = cutS(line);
  std::string parameter = cutS(line);

  std::forward_list< dmitriev::Book > result = findBooks(lib, dirName, query, parameter, 0);
  if (!result.empty())
  {
    lib.at(dirName).erase(result.front().key);
  }
}

void dmitriev::copyBook(library& lib, std::istream& inp)
{
  std::string line = "";
  std::getline(inp, line);

  std::string dirFrom = cutS(line);
  std::string dirTo = cutS(line);
  std::string query = cutS(line);
  std::string parameter = cutS(line);

  std::forward_list< dmitriev::Book > result = findBooks(lib, dirFrom, query, parameter, 0);
  if (!result.empty())
  {
    dmitriev::Book book = findBooks(lib, dirFrom, query, parameter, 0).front();
    lib.at(dirTo).insert({book.key, book});
  }
}

void printBook(const dmitriev::Book& book, std::ostream& out)
{
  out << "key: " << book.key << '\n';
  out << "title: " << book.title << '\n';
  out << "author: " << book.author << '\n';
  out << "isbn: " << book.isbn << '\n';
  out << "year: " << book.year;
}

void dmitriev::printFindedBooks(const library& lib, std::ostream& out, std::istream& inp)
{
  std::string line;
  std::getline(inp, line);

  std::forward_list< dmitriev::Book > result;
  std::string dirName = cutS(line);
  std::string query = cutS(line);
  std::string parameter = cutS(line);
  result = findBooks(lib, dirName, query, parameter, std::stol(cutS(line)));

  typename std::forward_list< dmitriev::Book >::const_iterator it = result.cbegin();
  if (it == result.cend())
  {
    out << "<EMPTY>";//
  }
  printBook(*it++, out);
  while (it != result.cend())
  {
    out << "\n\n";
    printBook(*it++, out);
  }
}
