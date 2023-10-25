#ifndef TLABSNEW_DICTIONARY_H
#define TLABSNEW_DICTIONARY_H
#include <map>
#include <string>
#include <vector>
#include "polygon.h"

namespace timofeev
{
  using dict = std::map< std::string, void (*)(std::istream&, const std::vector< Polygon >&) >;
  dict setDictionary();
}
#endif
