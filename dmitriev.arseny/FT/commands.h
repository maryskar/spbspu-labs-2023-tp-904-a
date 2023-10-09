#ifndef COMMANDS_H
#define COMMANDS_H

#include <unordered_map>
#include <iostream>
#include "book.h"

using direction = std::unordered_map< std::string, Book >;
using library = std::unordered_map< std::string, direction >;

void addBook(direction dir, Book book);
void deleteBook(direction dir, std::string parameter, std::string query);
void findBook(direction dir, std::string parameter, std::string query, size_t k, std::ostream& out);
void moveBook(direction from, direction to, std::string parameter, std::string query);

void printDirection(direction dir, std::ostream& out);
void createDirection(library& lib, std::string name);
void deleteDirection(library& lib, std::string name);
void combineDirection(library& lib, std::string name, std::string lhsName, std::string rhsName);
void saveDirection(library& lib, std::string name, std::ostream fileName);
void downloadDirection(library& lib, std::string name, std::istream fileName);

#endif
