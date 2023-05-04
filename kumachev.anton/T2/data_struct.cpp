#include "data_struct.h"
#include <iostream>

namespace kumachev {
  struct ProcessingState {
    bool key1;
    bool key2;
    bool key3;
  };

  static void processField(std::istream &istream, const std::string &field, DataStruct &dataStruct,
      ProcessingState &state);

  static int compareRational(const std::pair< long long, unsigned long long > &lhs,
      const std::pair< long long, unsigned long long > &rhs);
}

kumachev::StreamGuard::StreamGuard(std::basic_ios< char > &s):
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  fmt_(s.flags())
{}

kumachev::StreamGuard::~StreamGuard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}

std::istream &kumachev::operator>>(std::istream &istream, DataStruct &dataStruct)
{
  std::istream::sentry sentry(istream);

  if (!sentry) {
    return istream;
  }

  istream >> CharIO{ '(' } >> CharIO{ ':' };

  ProcessingState state{ false, false, false };
  DataStruct data;
  std::string key;

  istream >> key;
  processField(istream, key, data, state);
  istream >> key;
  processField(istream, key, data, state);
  istream >> key;
  processField(istream, key, data, state);
  istream >> CharIO{ ')' };

  if (istream) {
    if (!state.key1 || !state.key2 || !state.key3) {
      istream.setstate(std::ios::failbit);
    } else {
      dataStruct = data;
    }
  }

  return istream;
}

std::istream &kumachev::operator>>(std::istream &istream, CharIO &&character)
{
  std::istream::sentry sentry(istream);

  if (!sentry) {
    return istream;
  }

  char c = '\0';
  istream >> c;

  if (istream && (c != character.value)) {
    istream.setstate(std::ios::failbit);
  }

  return istream;
}

std::istream &kumachev::operator>>(std::istream &istream, UnsignedLongLongIO &&unsignedLongLong)
{
  std::istream::sentry sentry(istream);

  if (!sentry) {
    return istream;
  }

  unsigned long long ull = 0;
  istream >> ull >> CharIO{ 'u' } >> CharIO{ 'l' } >> CharIO{ 'l' };

  if (istream) {
    unsignedLongLong.value = ull;
  }

  return istream;
}

std::istream &kumachev::operator>>(std::istream &istream, FieldIO &&field)
{
  std::istream::sentry sentry(istream);

  if (!sentry) {
    return istream;
  }

  std::string s;
  istream >> s;

  if (istream) {
    field.value = s;
  }

  return istream;
}

std::istream &kumachev::operator>>(std::istream &istream, StringIO &&field)
{
  std::istream::sentry sentry(istream);

  if (!sentry) {
    return istream;
  }

  std::string s;
  istream >> CharIO{ '\"' };
  std::getline(istream, s, '\"');

  if (istream) {
    field.value = s;
  }

  return istream;
}

std::istream &kumachev::operator>>(std::istream &istream, PairIO &&pair)
{
  std::istream::sentry sentry(istream);

  if (!sentry) {
    return istream;
  }

  std::pair< long long, unsigned long long > value{ 0, 0 };

  istream >> CharIO{ '(' } >> CharIO{ ':' } >> CharIO{ 'N' } >> value.first
          >> CharIO{ ':' } >> CharIO{ 'D' } >> value.second >> CharIO{ ':' }
          >> CharIO{ ')' };

  if (istream) {
    pair.value = value;
  }

  return istream;
}

std::ostream &kumachev::operator<<(std::ostream &ostream, const DataStruct &dataStruct)
{
  std::ostream::sentry sentry(ostream);

  if (!sentry) {
    return ostream;
  }

  StreamGuard guard(ostream);
  ostream << "(:key1 " << dataStruct.key1 << "ull:key2 (:N " << dataStruct.key2.first
          << ":D " << dataStruct.key2.second << ":):key3 \"" << dataStruct.key3 << "\":)";

  return ostream;
}

static void kumachev::processField(std::istream &istream, const std::string &field, DataStruct &dataStruct,
    ProcessingState &state)
{
  std::istream::sentry sentry(istream);

  if (!sentry) {
  return;
  }

  if (!state.key1 && field == "key1") {
  state.key1 = true;
  istream >> UnsignedLongLongIO{ dataStruct.key1 } >> CharIO{ ':' };
  } else if (!state.key2 && field == "key2") {
  state.key2 = true;
  istream >> PairIO{ dataStruct.key2 } >> CharIO{ ':' };
  } else if (!state.key3 && field == "key3") {
  state.key3 = true;
  istream >> StringIO{ dataStruct.key3 } >> CharIO{ ':' };
  } else {
  istream.setstate(std::ios::failbit);
  }
}

bool kumachev::compareData(const DataStruct &lhs, const DataStruct &rhs)
{
  return (lhs.key1 < rhs.key1) || (lhs.key1 == rhs.key1 && compareRational(lhs.key2, rhs.key2) < 0)
      || (lhs.key1 == rhs.key1 && compareRational(lhs.key2, rhs.key2) == 0 && lhs.key3.size() <= rhs.key3.size());
}

static int kumachev::compareRational(const std::pair< long long int, unsigned long long int > &lhs,
    const std::pair< long long int, unsigned long long int > &rhs)
{
  auto diff = static_cast<float>(lhs.first) / lhs.second - static_cast<float>(rhs.first) / rhs.second;

  if (diff < 0) {
    return -1;
  } else if (diff > 0) {
    return 1;
  } else {
    return 0;
  }
}
