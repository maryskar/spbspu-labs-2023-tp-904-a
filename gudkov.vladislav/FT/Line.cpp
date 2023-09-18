#include "Line.h"

gudkov::Line::Line(char symbol)
{
  data_ += symbol;
}

gudkov::Line::Line(const char *cStr):
  data_(cStr)
{

}

gudkov::Line::Line(const std::string &str):
  data_(str)
{

}

void gudkov::Line::pushBack(char symbol)
{
  data_.push_back(symbol);
}

gudkov::Line::iterator gudkov::Line::begin() const
{
  return data_.begin();
}

gudkov::Line::iterator gudkov::Line::end() const
{
  return data_.end();
}

bool gudkov::Line::isEmpty() const
{
  return data_.empty();
}

void gudkov::Line::clear()
{
  data_.clear();
}

bool gudkov::Line::operator<(const Line &other) const
{
  return this->data_ < other.data_;
}

std::string gudkov::Line::toString() const
{
  return data_;
}

size_t gudkov::Line::length() const
{
  return data_.length();
}

std::istream &gudkov::operator>>(std::istream &in, Line &destination)
{
  std::getline(in, destination.data_);

  return in;
}

std::ostream &gudkov::operator<<(std::ostream &out, const Line &depature)
{
  out << depature.data_;
  return out;
}
