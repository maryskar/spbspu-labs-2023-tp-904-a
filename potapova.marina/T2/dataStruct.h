#include <string>

namespace potapova
{
  struct DataStruct
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char sign;
  };

  struct UnsignedLongIntOctIO
  {
    unsigned long long& oct;
  };

  struct UnsignedLongIntBinIO
  {
    unsigned long long& bin;
  };

  struct StringIO
  {
    std::string& str;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, UnsignedLongIntOctIO&& dest);
  std::istream& operator>>(std::istream& in, UnsignedLongIntBinIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

  struct Comparator
  {
    bool operator()(const DataStruct& that, const DataStruct& other);
  };
}
