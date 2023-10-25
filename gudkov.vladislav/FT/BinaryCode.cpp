#include "BinaryCode.h"

size_t gudkov::BinaryCode::size() const
{
  return data_.size();
}

bool gudkov::BinaryCode::operator[](size_t index) const
{
  return data_[index];
}

void gudkov::BinaryCode::pushBack(int bit)
{
  if (bit != 0 && bit != 1)
  {
    throw std::runtime_error("Wrong bit: 0 / 1 expected.\n");
  }

  data_.push_back(bit);
}

void gudkov::BinaryCode::popBack()
{
  data_.pop_back();
}

gudkov::BinaryCode::iterator gudkov::BinaryCode::begin() const
{
  return data_.begin();
}
gudkov::BinaryCode::iterator gudkov::BinaryCode::end() const
{
  return data_.end();
}

std::string gudkov::BinaryCode::toString() const
{
  std::string str;

  for (bool bit : data_)
  {
    str.push_back(bit + '0');
  }

  return str;
}

std::istream &gudkov::BinaryCode::readBinary(std::istream &in)
{
  data_.clear();

  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  unsigned char byte = 0;
  while (in.read(reinterpret_cast<char *>(&byte), sizeof(byte)))
  {
    for (size_t i = BinaryCode::bitsInByte_ - 1; i != not_position_; --i)
    {
      bool bit = byte & (1 << i);

      data_.push_back(bit);
    }
  }

  size_t countOfLastBits = static_cast<size_t>(char(byte));
  size_t countOfExtraBits;

  if (countOfLastBits == 0)
  {
    countOfExtraBits = BinaryCode::bitsInByte_;
  }
  else
  {
    countOfExtraBits = BinaryCode::bitsInByte_ + (BinaryCode::bitsInByte_ - countOfLastBits);
  }


  for (size_t i = 0; i < countOfExtraBits; ++i)
  {
    data_.pop_back();
  }

  return in;
}

std::ostream &gudkov::BinaryCode::writeBinary(std::ostream &out) const
{
  size_t shift = BinaryCode::bitsInByte_ - 1;
  unsigned char byte = 0;
  for (bool bit : data_)
  {
    byte |= (bit << shift);

    --shift;

    if (shift == not_position_)
    {
      out.write(reinterpret_cast<char *>(&byte), sizeof(byte));
      byte = 0;
      shift = BinaryCode::bitsInByte_ - 1;
    }
  }

  if (shift != BinaryCode::bitsInByte_ - 1)
  {
    out.write(reinterpret_cast<char *>(&byte), sizeof(byte));
  }

  byte = ((BinaryCode::bitsInByte_ - 1) - shift);
  out.write(reinterpret_cast<char *>(&byte), sizeof(byte));

  return out;
}

std::ostream &gudkov::operator<<(std::ostream &out, const BinaryCode &departure)
{
  for (bool bit : departure.data_)
  {
    out << bit;
  }
  out << std::endl;

  return out;
}
