#ifndef BOOK_H
#define BOOK_H

#include <string>

struct Book
{
  std::string key;
  std::string title;
  std::string author;
  std::string isbn;

  size_t year;
};



#endif
