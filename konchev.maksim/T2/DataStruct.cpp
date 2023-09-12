#include "DataStruct.h"
#include "iotypes.h"
#include "StreamGuard.h"
namespace konchev
{
  bool compareData(const DataStruct& lhs, const DataStruct& rhs)
  {
    if (lhs.key1 != rhs.key1)
    {
      return lhs.key1 < rhs.key1;
    }
    else if (lhs.key2 != rhs.key2)
    {
      return lhs.key2 < rhs.key2;
    }
    else
    {
      return lhs.key3.size() < rhs.key3.size();
    }
  }
  std::istream &operator>>(std::istream &in, DataStruct &data)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input_data;
    in >> delimiter{'('} >> delimiter{':'};
    for (std::size_t i = 0; i < 3; i++)
    {
      std::size_t num = 0;
      in >> label{"key"} >> num;
      if (num == 1)
      {
        in >> LongLong{input_data.key1} >> delimiter{':'};
      }
      else if (num == 2)
      {
        in >> uLongLong{input_data.key2} >> delimiter{':'};
      }
      else if (num == 3)
      {
        in >> String{input_data.key3} >> delimiter{':'};
      }
    }
    in >> delimiter{')'};
    if (in)
    {
      data = input_data;
    }
    return in;
  }
  std::ostream &operator<<(std::ostream &out, const DataStruct &data)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    StreamGuard streamGuard(out);
    out << "(:key1 " << std::dec << data.key1 << "ll";
    out << ":key2 0x" << std::hex << std::uppercase << data.key2;
    out << ":key3 \"" << data.key3 << "\":)";
    return out;
  }
}
