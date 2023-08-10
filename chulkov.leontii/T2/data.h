#ifndef DATA_H
#define DATA_H
#include <iomanip>
#include <string>

namespace chulkov {
  struct Data {
    unsigned long long key1;
    char key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, Data& dest);
  std::ostream& operator<<(std::ostream& out, const Data& dest);

  struct Comparator {
    bool operator()(const Data& frst, const Data& sec);
  };
}
#endif
