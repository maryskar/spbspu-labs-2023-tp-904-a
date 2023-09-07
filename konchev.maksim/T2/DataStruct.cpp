#include "DataStruct.h"
#include "../common/iotypes.h"
using namespace konchev;
std::ifstream &operator>>(std::ifstream &in, DataStruct &&data)
{
  std::ifstream::sentry sentry(in);
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
  if (in){
    data=input_data;
  }
  return in;
}
std::ofstream &operator<<(std::ofstream &out, const DataStruct &data)
{
  std::ofstream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
}
