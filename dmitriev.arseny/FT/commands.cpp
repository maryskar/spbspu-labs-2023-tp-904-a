#include "commands.h"
#include <forward_list>
#include <exception>
#include <fstream>
#include <algorithm>
#include <functional>

std::string dmitriev::cutS(std::string& line)
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

void dmitriev::addBook(library& lib, std::string& line)
{
  std::string dirName = cutS(line);

  Book newBook{cutS(line), cutS(line), cutS(line), cutS(line), std::stol(cutS(line))};
  if (lib.at(dirName).find(newBook.key) != lib.at(dirName).end())
  {
    throw std::invalid_argument("book alrady exist");
  }
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

dmitriev::Book getBook(const std::pair< std::string, dmitriev::Book >& entry)
{
  return entry.second;
}

bool isBookCorrect(const dmitriev::Book& entry,
  const std::string& query,
  const std::string& parameter,
  size_t k)
{
  bool p1 = (parameter == "year" && std::to_string(entry.year) == query);
  bool p2 = (parameter == "isbn" && entry.isbn == query);
  std::string rhsStr = parameter == "title" ? entry.title : entry.author;
  size_t distance = hammingDistance(query, rhsStr);
  bool p3 = (parameter == "title" || parameter == "author") && distance <= k;

  return p1 || p2 || p3;
}

std::forward_list< dmitriev::Book > findBooks(const dmitriev::library& lib,
  const std::string& dir,
  const std::string& query,
  const std::string& parameter,
  size_t k)
{
  std::forward_list< dmitriev::Book > result;
  std::forward_list< dmitriev::Book > books;

  std::transform(lib.at(dir).begin(), lib.at(dir).end(), std::front_inserter(books), getBook);

  auto it = std::begin(books);
  auto end = std::end(books);

  using namespace std::placeholders;
  auto isBookCor = std::bind(isBookCorrect, _1, query, parameter, k);
  std::copy_if(it, end, std::front_inserter(result), isBookCor);


  return result;
}

void dmitriev::deleteBook(library& lib, std::string& line)
{
  std::string dirName = cutS(line);
  std::string query = cutS(line);
  std::string parameter = cutS(line);

  std::forward_list< Book > result = findBooks(lib, dirName, query, parameter, 0);
  if (!result.empty())
  {
    lib.at(dirName).erase(result.front().key);
  }
}

void dmitriev::copyBook(library& lib, std::string& line)
{
  std::string dirFrom = cutS(line);
  std::string dirTo = cutS(line);
  std::string query = cutS(line);
  std::string parameter = cutS(line);

  std::forward_list< Book > result = findBooks(lib, dirFrom, query, parameter, 0);
  if (!result.empty())
  {
    Book newBook = result.front();
    if (lib.at(dirTo).find(newBook.key) != lib.at(dirTo).end())
    {
      throw std::invalid_argument("book alrady exist");
    }
    lib.at(dirTo)[newBook.key] = newBook;
  }
}

void dmitriev::createDirectory(library& lib, std::string& line)
{
  std::string dirName = cutS(line);
  if (lib.find(dirName) != lib.end())
  {
    throw std::invalid_argument("dir alrady exist");
  }
  lib[dirName];
}

void dmitriev::deleteDirectory(library& lib, std::string& line)
{
  std::string dirName = cutS(line);
  if (lib.find(dirName) == lib.end())
  {
    throw std::invalid_argument("dir not found");
  }

  lib.erase(dirName);
}

bool isBookExist(const std::pair< std::string, dmitriev::Book >& entry, const dmitriev::directory& dir)
{
  return dir.find(entry.first) == dir.end();
}

void dmitriev::combineDirectorys(library& lib, std::string& line)
{
  std::string newDirName = cutS(line);
  std::string lhsDirName = cutS(line);
  std::string rhsDirName = cutS(line);

  directory newDir = lib.at(lhsDirName);

  using namespace std::placeholders;
  auto isBookInDir = std::bind(isBookExist, _1, newDir);
  const directory& rhsDir = lib.at(rhsDirName);
  std::copy_if(rhsDir.begin(), rhsDir.end(), std::inserter(newDir, newDir.end()), isBookInDir);

  if (lib.find(newDirName) != lib.end())
  {
    throw std::invalid_argument("dir alrady exist");
  }
  lib[newDirName] = newDir;
}

void dmitriev::downloadDirectory(library& lib, std::string& line)
{
  std::string dirName = cutS(line);
  std::string fileName = cutS(line);

  std::ifstream file(fileName);
  if (!file.is_open())
  {
    throw std::invalid_argument("incorrect file name");
  }

  directory newDir;
  Book newBook;
  while (!file.eof())
  {
    file >> newBook;
    newDir[newBook.key] = newBook;
  }

  if (lib.find(dirName) != lib.end())
  {
    throw std::invalid_argument("dir alrady exist");
  }
  lib[dirName] = newDir;
}

void printBook(const dmitriev::Book& book, std::ostream& out)
{
  out << "key: " << book.key << '\n';
  out << "title: " << book.title << '\n';
  out << "author: " << book.author << '\n';
  out << "isbn: " << book.isbn << '\n';
  out << "year: " << book.year;
}

void dmitriev::printFindedBooks(const library& lib, std::string& line, std::ostream& out)
{
  std::string dirName = cutS(line);
  std::string query = cutS(line);
  std::string parameter = cutS(line);
  std::forward_list< Book > result = findBooks(lib, dirName, query, parameter, std::stol(cutS(line)));

  typename std::forward_list< Book >::const_iterator it = result.cbegin();
  if (it == result.cend())
  {
    return;
  }
  printBook(*it++, out);
  while (it != result.cend())
  {
    out << "\n\n";
    printBook(*it++, out);
  }
}

void dmitriev::printDirectory(const library& lib, std::string& line,std::ostream& out)
{
  std::string dirName = cutS(line);

  typename directory::const_iterator it = lib.at(dirName).cbegin();
  if (it == lib.at(dirName).cend())
  {
    return;
  }
  printBook(it->second, out);
  it++;
  for (;it != lib.at(dirName).cend(); it++)
  {
    out << "\n\n";
    printBook(it->second, out);
  }
}

void dmitriev::unloadDirectory(const library& lib, std::string& line, std::ostream& out)
{
  std::string dirName = cutS(line);
  std::string fileName = cutS(line);

  std::ofstream file(fileName);
  if (!file.is_open())
  {
    throw std::invalid_argument("incorrect file name");
  }

  typename directory::const_iterator it = lib.at(dirName).cbegin();
  for (; it != lib.at(dirName).cend(); it++)
  {
    file << it->second << '\n';
  }
}
