#ifndef STRUCT_IO_H
#define STRUCT_IO_H
#include <string>

struct delimiter_sep
{
  char sep;
};

struct delimiter_io
{
  char exp;
};

struct string_io
{
  std::string& ref;
};

struct DBL_sciIO
{
  double& ref;
};

struct ULL_hexIO
{
  unsigned long long& ref;
};



#endif
