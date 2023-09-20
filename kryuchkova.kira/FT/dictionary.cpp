#include "dictionary.h"
#include <stdexcept>

namespace kryuchkova
{
  ErDictionary::translations ErDictionary::find(const word & wrd) const
  {
    if (auto res = dict_.find(wrd); res != dict_.end())
    {
      return res->second; 
    }
    else
    {
      throw std::logic_error("Dict doesn't contain this word");
    }
  }
  void ErDictionary::insert(const word & wrd, const translations & trans)
  {
    if (!dict_.insert(std::pair< word, translations >(wrd, trans)).second)
    {
      throw std::logic_error("This word already exist in this dict");
    }
  }
  ErDictionary::word ErDictionary::getName() const
  {
    return name_;
  }



}