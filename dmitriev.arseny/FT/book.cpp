#include "book.h"
#include <iostream>

struct SeparatorIO
{
  char expected;
};
std::istream& operator>>(std::istream& inp, SeparatorIO&& data)
{
  std::istream::sentry sentry(inp);
  if (!sentry)
  {
    return inp;
  }

  char c = '\0';
  inp >> c;
  if (inp && c != data.expected)
  {
    inp.setstate(std::ios::failbit);
  }

  return inp;
}
std::ostream& operator<<(std::ostream& out, const SeparatorIO& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  return out << data.expected;
}


struct LableIO
{
  std::string expected;
};
std::istream& operator>>(std::istream& inp, LableIO&& data)
{
  std::istream::sentry sentry(inp);
  if (!sentry)
  {
    return inp;
  }

  for (size_t i = 0; i < data.expected.length(); i++)
  {
    inp >> SeparatorIO{data.expected[i]};
  }

  return inp;
}
std::ostream& operator<<(std::ostream& out, const LableIO& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  return out << data.expected;
}


struct StringI
{
  std::string& value;
};
std::istream& operator>>(std::istream& inp, StringI&& data)
{
  std::istream::sentry sentry(inp);
  if (!sentry)
  {
    return inp;
  }

  return std::getline(inp >> SeparatorIO{'"'}, data.value, '"');
}


struct StringO
{
  const std::string& value;
};
std::ostream& operator<<(std::ostream& out, const StringO& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  return out << SeparatorIO{'"'} << data.value << SeparatorIO{'"'};
}

std::istream& operator>>(std::istream& inp, Book& data)
{
  std::istream::sentry sentry(inp);
  if (!sentry)
  {
    return inp;
  }

  inp >> LableIO{"@Book"} >> SeparatorIO{'{'};

  Book input;
  std::getline(inp, input.key, ',');
  for (size_t i = 0; i < 4; i++)
  {
    if (i > 0)
    {
      inp >> SeparatorIO{','};
    }
    std::string field = "";
    inp >> field;


    if (field == "title")
    {
      inp >> SeparatorIO{'='} >> StringI{input.title};
    }
    else if (field == "author")
    {
      inp >> SeparatorIO{'='} >> StringI{input.author};
    }
    else if (field == "isbn")
    {
      inp >> SeparatorIO{'='} >> StringI{input.isbn};
    }
    else if (field == "year")
    {
      inp >> SeparatorIO{'='} >> input.year;
    }
    else
    {
      inp.setstate(std::ios::failbit);
    }
    if (!sentry)
    {
      return inp;
    }
  }
  inp >> SeparatorIO{'}'};

  if (inp)
  {
    data = input;
  }

  return inp;
}

std::ostream& operator<<(std::ostream& out, Book& data)
{
  out << "@Book{" << data.key << ",\n";
  out << "  " << "author = " << StringO{data.author} << ",\n";
  out << "  " << "title = " << StringO{data.title} << ",\n";
  out << "  " << "year = " << data.year << ",\n";
  out << "  " << "isbn = " << StringO{data.isbn} << "\n";
  out << "}";

  return out;
}
