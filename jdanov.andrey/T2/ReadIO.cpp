#include "ReadIO.h"

std::istream& zhdanov::operator>>(std::istream& input, DelimiterIO&& delimeter)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  char symbol = '0';
  input >> symbol;
  if (input.good() && (symbol != delimeter.expected))
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

std::istream& zhdanov::operator>>(std::istream& input, LongLongIO&& number)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  input >> number.reference;
  input >> DelimiterIO{'l'} >> DelimiterIO{'l'};
  return input;
}

std::istream& zhdanov::operator>>(std::istream& input, StringIO&& string)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  input >> DelimiterIO{'"'};
  std::getline(input, string.reference, '"');
  return input;
}

std::istream& zhdanov::operator>>(std::istream& input, WordIO&& string)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  input >> string.reference;
  return input;
}

std::istream& zhdanov::operator>>(std::istream& input, BinaryIO&& binaryNumber)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  std::string data = "";
  std::getline(input, data, ':');
  try
  {
    binaryNumber.refence = toDecimal(data);
  }
  catch (std::runtime_error)
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

std::string zhdanov::toBinary(unsigned long long decimalNumber)
{
  unsigned long long number = decimalNumber;
  std::string result = "";
  do
  {
    if (number % 2 == 1)
    {
      result += '1';
    }
    else
    {
      result += '0';
    }
    number = number / 2;
  } while (number != 0);
  std::reverse(result.begin(), result.end());
  return result;
}

unsigned long long zhdanov::toDecimal(const std::string& binaryNumber)
{
  if (binaryNumber.size() <= 2 || binaryNumber[0] != '0' || binaryNumber[1] != 'b')
  {
    throw std::runtime_error("Invalid binary literal.\n");
  }
  std::string number(binaryNumber.begin() + 2, binaryNumber.end());
  unsigned long long result = 0;
  for (size_t i = 0; i < number.size(); ++i)
  {
    if (number[i] == '0')
    {
      result = result * 2;
    }
    else if (number[i] == '1')
    {
      result = result * 2 + 1;
    }
    else
    {
      throw std::runtime_error("Invalid binary literal.\n");
    }
  }
  return result;
}
