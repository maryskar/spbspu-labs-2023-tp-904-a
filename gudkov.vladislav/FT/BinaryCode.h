#ifndef BINARY_CODE_H
#define BINARY_CODE_H

#include <iostream>
#include <vector>
#include <string>

namespace gudkov
{
  class BinaryCode
  {
  public:
    using iterator = std::vector< bool >::const_iterator;

    BinaryCode() = default;
    ~BinaryCode() = default;

    BinaryCode(const BinaryCode &other) = default;
    BinaryCode &operator=(const BinaryCode &other) = default;

    BinaryCode(BinaryCode &&other) = default;
    BinaryCode &operator=(BinaryCode &&other) = default;

    size_t size() const;
    bool operator[](size_t index) const;

    void pushBack(int bit);
    void popBack();

    iterator begin() const;
    iterator end() const;

    std::string toString() const;

    std::istream &readBinary(std::istream &in);
    std::ostream &writeBinary(std::ostream &out) const;
  private:
    static const size_t bitsInByte_ = 8;
    static const size_t not_position_ = -1;

    std::vector< bool > data_;

    friend std::ostream &operator<<(std::ostream &out, const BinaryCode &departure);
  };
}
#endif
