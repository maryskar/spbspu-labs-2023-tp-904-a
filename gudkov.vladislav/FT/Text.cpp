#include "Text.h"

gudkov::Text::Text(char symbol):
  Text(Line(symbol))
{

}

gudkov::Text::Text(const char *cStr):
  Text(Line(cStr))
{

}

gudkov::Text::Text(const std::string &str):
  Text(Line(str))
{

}

gudkov::Text::Text(const Line &line)
{
  data_.push_back(line);
}

gudkov::Text::Text(const std::vector< Line > &text):
  data_(text)
{

}

void gudkov::Text::pushBack(const Line &line)
{
  data_.push_back(line);
}

gudkov::Text::iterator gudkov::Text::begin() const
{
  return data_.begin();
}

gudkov::Text::iterator gudkov::Text::end() const
{
  return data_.end();
}

gudkov::Text &gudkov::Text::operator+=(const Text &other)
{
  data_.insert(data_.end(), other.begin(), other.end());

  return *this;
}

gudkov::Text gudkov::Text::operator+(const Text &other) const
{
  Text result = *this;

  result += other;

  return result;
}

std::istream &gudkov::operator>>(std::istream &in, Text &destination)
{
  Line line;
  while (in >> line)
  {
    if (!in.eof())
    {
      line.pushBack('\n');
    }

    destination.data_.push_back(line);
  }

  if (in.eof())
  {
    in.clear();
  }

  return in;
}

std::ostream &gudkov::operator<<(std::ostream &out, const Text &depature)
{
  for (const Line &line : depature.data_)
  {
    out << line;
  }

  return out;
}
