#include "dictionary.h"
#include <stdexcept>
#include <algorithm>

namespace kryuchkova
{
  ErDictionary::ErDictionary()
  {}

  ErDictionary::ErDictionary(std::string & name):
   name_(name)
  {}

  ErDictionary::ErDictionary(std::string & name, std::map< word, translations > & dict):
   name_(name),
   dict_(dict)
  {}

  ErDictionary::translations ErDictionary::find(const word & wrd) const
  {
    auto res = dict_.find(wrd);
    if (res != dict_.end())
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
      throw std::logic_error("This word already exists in this dict");
    }
  }

  ErDictionary::word ErDictionary::getName() const
  {
    return name_;
  }

  std::map< ErDictionary::word, ErDictionary::translations > ErDictionary::getDict() const
  {
    return dict_;
  }

  void ErDictionary::setName(const std::string & name)
  {
    name_ = name;
  }

  void ErDictionary::erase(const word & wrd)
  {
    dict_.erase(wrd);
  }

  size_t ErDictionary::size() const
  {
    return dict_.size();
  }

  std::ostream & operator<<(std::ostream & out, const ErDictionary & dict)
  {
    out << dict.getName() << '\n';
    for (const auto & pair: dict.getDict())
    {
      out << pair.first << ": ";
      std::copy(pair.second.begin(), pair.second.end(), std::ostream_iterator< std::string >(out, " "));
      out << '\n';
    }
    return out;
  }

  std::istream & operator>>(std::istream & in, ErDictionary & dict)
  {
    while (!in.eof())
    {
      std::istream::sentry sentry(in);
      if (!sentry)
      {
        return in;
      }
      std::string word = "";
      in >> word;
      int n_translations = 0;
      in >> n_translations;
      std::vector< std::string > translations;
      std::copy_n(std::istream_iterator< std::string >(in), n_translations, std::back_inserter(translations));
      dict.insert(word, translations);
    }
    return in;
  }
}
