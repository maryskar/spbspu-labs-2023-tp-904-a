#include "io.h"
#include <iostream>
#include "stream_guard.h"
#include "basic_io.h"

namespace kumachev {
  struct ProcessingState {
    bool key1;
    bool key2;
    bool key3;
  };

  static void processField(std::istream &istream, const std::string &field,
      DataStruct &dataStruct, ProcessingState &state)
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
      istream >> RationalIO{ dataStruct.key2 } >> CharIO{ ':' };
    } else if (!state.key3 && field == "key3") {
      state.key3 = true;
      istream >> StringIO{ dataStruct.key3 } >> CharIO{ ':' };
    } else {
      istream.setstate(std::ios::failbit);
    }
  }

  std::istream &operator>>(std::istream &istream, DataStruct &dataStruct)
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

  std::istream &operator>>(std::istream &istream, UnsignedLongLongIO &&ullIO)
  {
    std::istream::sentry sentry(istream);

    if (!sentry) {
      return istream;
    }

    unsigned long long ull = 0;
    istream >> ull >> CharIO{ 'u' } >> CharIO{ 'l' } >> CharIO{ 'l' };

    if (istream) {
      ullIO.value = ull;
    }

    return istream;
  }

  std::istream &operator>>(std::istream &istream, FieldIO &&field)
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

  std::istream &operator>>(std::istream &istream, StringIO &&field)
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

  std::istream &operator>>(std::istream &istream, RationalIO &&rationalIO)
  {
    std::istream::sentry sentry(istream);

    if (!sentry) {
      return istream;
    }

    rational value{ 0, 0 };

    istream >> CharIO{ '(' } >> CharIO{ ':' } >> CharIO{ 'N' } >> value.first;
    istream >> CharIO{ ':' } >> CharIO{ 'D' } >> value.second >> CharIO{ ':' };
    istream >> CharIO{ ')' };

    if (istream) {
      rationalIO.value = value;
    }

    return istream;
  }

  std::ostream &operator<<(std::ostream &ostream, const DataStruct &dataStruct)
  {
    std::ostream::sentry sentry(ostream);

    if (!sentry) {
      return ostream;
    }

    StreamGuard guard(ostream);
    ostream << "(:key1 " << dataStruct.key1 << "ull:key2 (:N ";
    ostream << dataStruct.key2.first << ":D " << dataStruct.key2.second;
    ostream << ":):key3 \"" << dataStruct.key3 << "\":)";

    return ostream;
  }
}
