#include "customtypes.h"

std::istream& dmitriev::operator>>(std::istream& inp, SeparatorIO&& data)
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

std::ostream& dmitriev::operator<<(std::ostream& inp, const SeparatorIO& data)
{
  // TODO: вставьте здесь оператор return
}

std::istream& dmitriev::operator>>(std::istream& inp, LableIO&& data)
{
  // TODO: вставьте здесь оператор return
}

std::ostream& dmitriev::operator<<(std::ostream& inp, const LableIO& data)
{
  // TODO: вставьте здесь оператор return
}

std::istream& dmitriev::operator>>(std::istream& inp, DoubleI&& data)
{
  // TODO: вставьте здесь оператор return
}

std::ostream& dmitriev::operator<<(std::ostream& inp, const DoubleO& data)
{
  // TODO: вставьте здесь оператор return
}

std::istream& dmitriev::operator>>(std::istream& inp, LongLongI&& data)
{
  // TODO: вставьте здесь оператор return
}

std::ostream& dmitriev::operator<<(std::ostream& inp, const LongLongO& data)
{
  // TODO: вставьте здесь оператор return
}

std::istream& dmitriev::operator>>(std::istream& inp, StringI&& data)
{
  // TODO: вставьте здесь оператор return
}

std::ostream& dmitriev::operator<<(std::ostream& inp, const StringO& data)
{
  // TODO: вставьте здесь оператор return
}
