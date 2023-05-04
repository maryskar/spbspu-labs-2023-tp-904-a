#include "data_struct.h"
#include <iostream>
#include <iomanip>

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

void kumachev::processField(std::istream &istream, const std::string &field, kumachev::DataStruct &dataStruct,
    kumachev::ProcessingState &state)
{
  std::istream::sentry sentry(istream);

  if (!sentry) {
    return;
  }

  if (!state.key1 && field == "key1") {
    state.key1 = true;
    istream >> kumachev::UnsignedLongLongIO{ dataStruct.key1 } >> kumachev::CharIO{ ':' };
  } else if (!state.key2 && field == "key2") {
    state.key2 = true;
    istream >> kumachev::PairIO{ dataStruct.key2 } >> kumachev::CharIO{ ':' };
  } else if (!state.key3 && field == "key3") {
    state.key3 = true;
    istream >> kumachev::StringIO{ dataStruct.key3 } >> kumachev::CharIO{ ':' };
  } else {
    istream.setstate(std::ios::failbit);
  }
}

std::istream &kumachev::operator>>(std::istream &istream, kumachev::DataStruct &dataStruct)
{
  std::istream::sentry sentry(istream);

  if (!sentry) {
    return istream;
  }

  istream >> kumachev::CharIO{ '(' } >> kumachev::CharIO{ ':' };

  kumachev::ProcessingState state{ false, false, false };
  kumachev::DataStruct data;
  std::string key;

  istream >> key;
  processField(istream, key, data, state);
  istream >> key;
  processField(istream, key, data, state);
  istream >> key;
  processField(istream, key, data, state);
  istream >> kumachev::CharIO{ ')' };

  if (istream) {
    if (!state.key1 || !state.key2 || !state.key3) {
      istream.setstate(std::ios::failbit);
    } else {
      dataStruct = data;
    }
  }

  return istream;
}

std::istream &kumachev::operator>>(std::istream &istream, kumachev::CharIO &&character)
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

std::istream &kumachev::operator>>(std::istream &istream, kumachev::UnsignedLongLongIO &&unsignedLongLong)
{
  std::istream::sentry sentry(istream);

  if (!sentry) {
    return istream;
  }

  unsigned long long ull = 0;
  istream >> ull >> kumachev::CharIO{ 'u' } >> kumachev::CharIO{ 'l' } >> kumachev::CharIO{ 'l' };

  if (istream) {
    unsignedLongLong.value = ull;
  }

  return istream;
}

std::istream &kumachev::operator>>(std::istream &istream, kumachev::FieldIO &&field)
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

std::istream &kumachev::operator>>(std::istream &istream, kumachev::StringIO &&field)
{
  std::istream::sentry sentry(istream);

  if (!sentry) {
    return istream;
  }

  std::string s;
  istream >> kumachev::CharIO{ '\"' };
  std::getline(istream, s, '\"');

  if (istream) {
    field.value = s;
  }

  return istream;
}

std::istream &kumachev::operator>>(std::istream &istream, kumachev::PairIO &&pair)
{
  std::istream::sentry sentry(istream);

  if (!sentry) {
    return istream;
  }

  std::pair< long long, unsigned long long > value{ 0, 0 };

  istream >> kumachev::CharIO{ '(' } >> kumachev::CharIO{ ':' } >> kumachev::CharIO{ 'N' } >> value.first
          >> kumachev::CharIO{ ':' } >> kumachev::CharIO{ 'D' } >> value.second >> kumachev::CharIO{ ':' }
          >> kumachev::CharIO{ ')' };

  if (istream) {
    pair.value.first = value.first;
    pair.value.second = value.second;
  }

  return istream;
}

std::ostream &kumachev::operator<<(std::ostream &ostream, const kumachev::DataStruct &dataStruct)
{
  std::ostream::sentry sentry(ostream);

  if (!sentry) {
    return ostream;
  }

  kumachev::StreamGuard guard(ostream);
  ostream << "(:key1 " << dataStruct.key1 << "ull:key2 (:N " << dataStruct.key2.first
          << ":D " << dataStruct.key2.second << ":):key3 \"" << dataStruct.key3 << "\":)";

  return ostream;
}
