#include "data_struct.h"
#include <iostream>
#include "iofmt_guard.h"
#include "struct_io.h"

std::istream& structure::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
  DataStruct in_data;
  in >> delimiter_sep{'('} >> delimiter_sep{':'};
  for (int i = 0; i < 3; ++i)
  {
    std::string keyX = "";
    in >> keyX;
    if (keyX == "key1")
    {

    }
    else if (keyX == "key2")
    {

    }
    else if (keyX == "key3")
    {

    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    in >> delimiter_sep{':'};
  }

}