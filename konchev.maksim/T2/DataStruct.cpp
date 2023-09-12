#include "DataStruct.h"
#include "iotypes.h"
#include "StreamGuard.h"
namespace konchev
{
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
    out << "(:key1 " << data.key1;
    out << ":key2 0x" << std::hex << std::uppercase << data.key2;
    out << ":key3 \"" << data.key3 << "\":)";
    return out;
  }
}
