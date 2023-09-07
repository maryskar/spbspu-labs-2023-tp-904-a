#include "DataStruct.h"
std::ifstream &operator>>(std::ifstream &in, DataStruct &&data)
{
  std::ifstream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
}
std::ofstream &operator<<(std::ofstream &out, const DataStruct &data)
{
  std::ofstream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
}
