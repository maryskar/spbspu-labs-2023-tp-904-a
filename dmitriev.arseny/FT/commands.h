#ifndef COMMANDS_H
#define COMMANDS_H

#include <unordered_map>
#include <iostream>
#include "book.h"

namespace dmitriev
{
  using directory = std::unordered_map< std::string, dmitriev::Book >;
  using library = std::unordered_map< std::string, directory >;


  void addBook(library& lib, std::istream& inp);
  void deleteBook(library& lib, std::istream& inp);
  void copyBook(library& lib, std::istream& inp);
  void createDirectory(library& lib, std::istream& inp);
  void deleteDirectory(library& lib, std::istream& inp);
  void combineDirectorys(library& lib, std::istream& inp);
  void downloadDirectory(library& lib, std::istream& inp);

  void printFindedBooks(const library& lib, std::ostream& out, std::istream& inp);
  void printDirectory(const library& lib, std::ostream& out, std::istream& inp);
  void unloadDirectory(const library& lib, std::ostream& out, std::istream& inp);

}

#endif
