#include "data_struct.h"
#include <iostream>
#include <iomanip>

T2::StreamGuard::StreamGuard(std::basic_ios< char > &s):
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  fmt_(s.flags())
{
}

T2::StreamGuard::~StreamGuard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}

void T2::processField(std::istream &istream, const std::string &field, T2::DataStruct &dataStruct,
                             T2::ProcessingState &state)
{
  std::istream::sentry sentry(istream);

  if (!sentry) {
    return;
  }

  if (!state.key1 && field == "key1") {
    state.key1 = true;
    istream >> T2::UnsignedLongLongIO{ dataStruct.key1 } >> T2::CharIO{ ':' };
  }
  else if (!state.key2 && field == "key2") {
    state.key2 = true;
    istream >> T2::PairIO{ dataStruct.key2 } >> T2::CharIO{ ':' };
  }
  else if (!state.key3 && field == "key3") {
    state.key3 = true;
    istream >> T2::StringIO{ dataStruct.key3 } >> T2::CharIO{ ':' };
  }
  else {
    istream.setstate(std::ios::failbit);
  }
}

std::istream &T2::operator>>(std::istream &istream, T2::DataStruct &dataStruct)
{
  std::istream::sentry sentry(istream);

  if (!sentry) {
    return istream;
  }

  istream >> T2::CharIO{ '(' } >> T2::CharIO{ ':' };

  T2::ProcessingState state{ false, false, false };
  T2::DataStruct data;
  std::string key;

  istream >> key;
  processField(istream, key, data, state);
  istream >> key;
  processField(istream, key, data, state);
  istream >> key;
  processField(istream, key, data, state);
  istream >> T2::CharIO{ ')' };

  if (istream) {
    if (!state.key1 || !state.key2 || !state.key3) {
      istream.setstate(std::ios::failbit);
    }
    else {
      dataStruct = data;
    }
  }

  return istream;
}

std::istream &T2::operator>>(std::istream &istream, T2::CharIO &&character)
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

std::istream &T2::operator>>(std::istream &istream, T2::UnsignedLongLongIO &&unsignedLongLong)
{
  std::istream::sentry sentry(istream);

  if (!sentry) {
    return istream;
  }

  unsigned long long ull = 0;
  istream >> ull >> T2::CharIO{ 'u' } >> T2::CharIO{ 'l' } >> T2::CharIO{ 'l' };

  if (istream) {
    unsignedLongLong.value = ull;
  }

  return istream;
}

std::istream &T2::operator>>(std::istream &istream, T2::FieldIO &&field)
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

std::istream &T2::operator>>(std::istream &istream, T2::StringIO &&field)
{
  std::istream::sentry sentry(istream);

  if (!sentry) {
    return istream;
  }

  std::string s;
  istream >> T2::CharIO{ '\"' };
  std::getline(istream, s, '\"');

  if (istream) {
    field.value = s;
  }

  return istream;
}

std::istream &T2::operator>>(std::istream &istream, T2::PairIO &&pair)
{
  std::istream::sentry sentry(istream);

  if (!sentry) {
    return istream;
  }

  std::pair< long long, unsigned long long > value{ 0, 0 };

  istream >> T2::CharIO{ '(' } >> T2::CharIO{ ':' } >> T2::CharIO{ 'N' } >> value.first
          >> T2::CharIO{ ':' } >> T2::CharIO{ 'D' } >> value.second >> T2::CharIO{ ':' }
          >> T2::CharIO{ ')' };

  if (istream) {
    pair.value.first = value.first;
    pair.value.second = value.second;
  }

  return istream;
}

std::ostream &T2::operator<<(std::ostream &ostream, const T2::DataStruct &dataStruct)
{
  std::ostream::sentry sentry(ostream);

  if (!sentry) {
    return ostream;
  }

  T2::StreamGuard guard(ostream);
  ostream << "(:key1 " << dataStruct.key1 << "ull:key2 (:N " << dataStruct.key2.first
          << ":D " << dataStruct.key2.second << ":):key3 \"" << dataStruct.key3 << "\":)\n";

  return ostream;
}
