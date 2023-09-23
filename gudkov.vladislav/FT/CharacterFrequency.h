#ifndef CHARACTER_FREQUENCY_H
#define CHARACTER_FREQUENCY_H

#include <iostream>
#include <vector>
#include <utility>
#include "Text.h"

namespace gudkov
{
  class CharacterFrequency
  {
  public:
    CharacterFrequency();
    CharacterFrequency(const Text &input);
    ~CharacterFrequency() = default;

    CharacterFrequency(const CharacterFrequency &) = default;
    CharacterFrequency &operator=(const CharacterFrequency &) = default;

    CharacterFrequency(CharacterFrequency &&) = default;
    CharacterFrequency &operator=(CharacterFrequency &&) = default;

    void fillBy(const Text &input);

    char getFirstChar() const;

    size_t size() const;

    bool isEmpty() const;

    void splitTwoParts(std::pair<CharacterFrequency, CharacterFrequency> &parts) const;

  private:
    friend std::ostream &operator<<(std::ostream &out, const CharacterFrequency &departure);
    friend std::istream &operator>>(std::istream &in, CharacterFrequency &destination);

    std::vector< std::pair < char, size_t >> data_;
    size_t frequencySum_;
  };
}
#endif
