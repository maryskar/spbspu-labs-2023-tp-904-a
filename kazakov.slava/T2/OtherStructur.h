#ifndef T2_OTHERSTRUCTUR_H
#define T2_OTHERSTRUCTUR_H
#include <string>
#include <iostream>

namespace kazakov
{
  struct ExpectedSymbol
  {
    char symbol = '.';
  };
  struct ExpectedChar
  {
    char bukva = '.';
  };
  struct ExpectedString
  {
    std::string string = "";
  };
  struct ExpectedLongLong
  {
    long long ll = 0;
  };
  std::istream& operator>>(std::istream& in, ExpectedSymbol&& dest);
  std::istream& operator>>(std::istream& in, ExpectedString& dest);
  std::istream& operator>>(std::istream& in, ExpectedLongLong& dest);
  std::istream& operator>>(std::istream& in, ExpectedChar& dest);
  std::ostream& operator<<(std::ostream& out, const ExpectedString& dest);
  std::ostream& operator<<(std::ostream& out, const ExpectedLongLong& dest);
  std::ostream& operator<<(std::ostream& out, const ExpectedChar& dest);
  bool operator<(const ExpectedLongLong& dest, const ExpectedLongLong& otherdest);
  bool operator<(const ExpectedLongLong& dest, long long chislo);
  bool operator<(const ExpectedChar& dest, const ExpectedChar& otherdest);
  bool operator<(const ExpectedString& dest, const ExpectedString& otherdest);
  bool operator==(const ExpectedChar& dest, const ExpectedChar& otherdest);
  bool operator==(const ExpectedLongLong& dest, const ExpectedLongLong& otherdest);
#endif
}
