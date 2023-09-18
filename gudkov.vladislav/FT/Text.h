#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <vector>
#include <string>
#include "Line.h"

namespace gudkov
{
  class Text
  {
  public:
    using iterator = std::vector< Line >::const_iterator;

    Text() = default;
    ~Text() = default;

    Text(const Text &other) = default;
    Text &operator=(const Text &other) = default;

    Text(Text &&other) = default;
    Text &operator=(Text &&other) = default;

    Text(char symbol);
    Text(const char *cStr);
    Text(const std::string &str);
    Text(const Line &line);
    Text(const std::vector< Line > &text);

    void pushBack(const Line &line);

    iterator begin() const;
    iterator end() const;

    Text &operator+=(const Text &other);
    Text operator+(const Text &other) const;
  private:
    std::vector< Line > data_;

    friend std::istream &operator>>(std::istream &in, Text &destination);
    friend std::ostream &operator<<(std::ostream &out, const Text &depature);
  };
}
#endif
