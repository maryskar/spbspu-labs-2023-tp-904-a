#ifndef T2_DATA_STRUCT_H
#define T2_DATA_STRUCT_H

#include <string>
#include <ios>
#include <bits/stl_pair.h>

namespace kumachev {
  struct DataStruct {
    unsigned long long key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };

  struct ProcessingState {
    bool key1;
    bool key2;
    bool key3;
  };

  struct CharIO {
    char value;
  };

  struct FieldIO {
    std::string &value;
  };

  struct StringIO {
    std::string &value;
  };

  struct UnsignedLongLongIO {
    unsigned long long &value;
  };

  struct PairIO {
    std::pair< long long, unsigned long long > &value;
  };

  class StreamGuard {
  public:
    explicit StreamGuard(std::basic_ios< char > &s);
    ~StreamGuard();
  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };

  void processField(std::istream &istream, const std::string &field, kumachev::DataStruct &dataStruct,
      kumachev::ProcessingState &state);

  std::istream &operator>>(std::istream &istream, kumachev::DataStruct &dataStruct);
  std::istream &operator>>(std::istream &istream, kumachev::CharIO &&character);
  std::istream &operator>>(std::istream &istream, kumachev::FieldIO &&field);
  std::istream &operator>>(std::istream &istream, kumachev::StringIO &&field);
  std::istream &operator>>(std::istream &istream, kumachev::UnsignedLongLongIO &&unsignedLongLong);
  std::istream &operator>>(std::istream &istream, kumachev::PairIO &&pair);

  std::ostream &operator<<(std::ostream &ostream, const kumachev::DataStruct &dataStruct);
}

#endif //T2_DATA_STRUCT_H
