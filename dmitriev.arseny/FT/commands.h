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
  void moveBook(library& lib, std::istream& inp);
  void createDirection(library& lib, std::istream& inp);
  void deleteDirection(library& lib, std::istream& inp);
  void combineDirection(library& lib, std::istream& inp);
  void downloadDirection(library& lib, std::istream& inp);

  void printFindedBooks(const library& lib, const std::string name, std::ostream& out, std::istream& inp);
  void printDirection(const library& lib, const std::string name, std::ostream& out, std::istream& inp);
  void unloadDirection(const library& lib, const std::string name, std::ostream& out, std::istream& inp);

}

#endif
