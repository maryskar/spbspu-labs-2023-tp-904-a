#include "dictionary.h"
#include <stdexcept>

namespace kryuchkova
{
  ErDictionary::translations ErDictionary::find(const ErDictionary::word & word) const
  {
    if (auto res = dict_.find(word); res != dict_.end())
    {
      return res->second; 
    }
    else
    {
      throw std::logic_error("Dict doesn't contain this word");
    }
  }

}