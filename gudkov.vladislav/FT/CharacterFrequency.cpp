#include "CharacterFrequency.h"
#include <map>
#include <algorithm>

gudkov::CharacterFrequency::CharacterFrequency():
  frequencySum_(0),
  data_()
{

}

gudkov::CharacterFrequency::CharacterFrequency(const Text &input):
  CharacterFrequency()
{
  fillBy(input);
}

void gudkov::CharacterFrequency::fillBy(const Text &input)
{
  data_.clear();

  std::map< char, size_t > alphabet;

  for (const Line &line : input)
  {
    for (char character : line)
    {
      ++alphabet[character];
      ++frequencySum_;
    }
  }

  data_.reserve(alphabet.size());

  for (const auto &elem : alphabet)
  {
    data_.push_back(elem);
  }

  const auto isLess = [](const std::pair <char, size_t> &a, const std::pair <char, size_t> &b) -> bool
    {
      return a.second > b.second;
    };

  std::sort(data_.begin(), data_.end(), isLess);
}

char gudkov::CharacterFrequency::getFirstChar() const
{
  return data_[0].first;
}

size_t gudkov::CharacterFrequency::size() const
{
  return data_.size();
}

bool gudkov::CharacterFrequency::isEmpty() const
{
  return data_.empty();
}

void gudkov::CharacterFrequency::splitTwoParts(std::pair<CharacterFrequency, CharacterFrequency> &parts) const
{
  size_t accumulatedSum = 0;

  auto separator = this->data_.begin();

  while (accumulatedSum < this->frequencySum_ / 2)
  {
    accumulatedSum += separator->second;
    ++separator;
  }

  parts.first.data_.insert(parts.first.data_.begin(), this->data_.begin(), separator);
  parts.first.frequencySum_ = accumulatedSum;

  parts.second.data_.insert(parts.second.data_.begin(), separator, this->data_.end());
  parts.second.frequencySum_ = this->frequencySum_ - accumulatedSum;
}

std::ostream &gudkov::operator<<(std::ostream &out, const CharacterFrequency &departure)
{
  for (const auto &elem : departure.data_)
  {
    out << elem.first << ": " << elem.second << std::endl;
  }

  return out;
}

std::istream &gudkov::operator>>(std::istream &in, CharacterFrequency &destination)
{
  destination.data_.clear();
  destination.frequencySum_ = 0;

  while (!in.eof())
  {
    char symbol = in.get();

    if (in.eof())
    {
      break;
    }

    if (!in)
    {
      throw std::runtime_error("Wrong symbol frequency: letter is missing.\n");
    }

    in.get();

    if (!in)
    {
      throw std::runtime_error("Wrong symbol frequency: symbol ':' is missing.\n");
    }

    in.get();

    if (!in)
    {
      throw std::runtime_error("Wrong symbol frequency: space is missing.\n");
    }

    size_t frequency = 0;
    in >> frequency;

    if (!in)
    {
      throw std::runtime_error("Wrong symbol frequency: frequency is missing.\n");
    }

    destination.data_.push_back(std::pair< char, size_t >(symbol, frequency));
    destination.frequencySum_ += frequency;

    in.get();
  }

  return in;
}
