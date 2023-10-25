#ifndef COMMANDS_H
#define COMMANDS_H

#include <unordered_map>
#include <iostream>
#include "book.h"

namespace dmitriev
{
  using directory = std::unordered_map< std::string, dmitriev::Book >;
  using library = std::unordered_map< std::string, directory >;

  std::string cutS(std::string& line);

  void addBook(library& lib, std::string& line);
  void deleteBook(library& lib, std::string& line);
  void copyBook(library& lib, std::string& line);
  void createDirectory(library& lib, std::string& line);
  void deleteDirectory(library& lib, std::string& line);
  void combineDirectorys(library& lib, std::string& line);
  void downloadDirectory(library& lib, std::string& line);

  void printFindedBooks(const library& lib, std::string& line, std::ostream& out);
  void printDirectory(const library& lib, std::string& line, std::ostream& out);
  void unloadDirectory(const library& lib, std::string& line, std::ostream& out);

}

#endif
