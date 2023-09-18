#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <string>

namespace gudkov
{
  class Line
  {
  public:
    using iterator = std::string::const_iterator;

    Line() = default;
    ~Line() = default;

    Line(const Line &other) = default;
    Line &operator=(const Line &other) = default;

    Line(Line &&other) = default;
    Line &operator=(Line &&other) = default;

    Line(char symbol);
    Line(const char *cStr);
    Line(const std::string &str);

    void pushBack(char symbol);

    iterator begin() const;
    iterator end() const;

    bool isEmpty() const;
    void clear();

    bool operator<(const Line &other) const;

    std::string toString() const;

    size_t length() const;
  private:
    std::string data_;

    friend std::istream &operator>>(std::istream &in, Line &destination);
    friend std::ostream &operator<<(std::ostream &out, const Line &depature);
  };
}
#endif
