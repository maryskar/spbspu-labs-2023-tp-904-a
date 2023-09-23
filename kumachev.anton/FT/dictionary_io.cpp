#include "dictionary_io.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

namespace kumachev {
  using entry = DictEntryIO;

  static DictEntryIO transformPairToEntry(const er_pair &pair)
  {
    return { pair.first, pair.second };
  }

  static er_pair transformEntryToPair(const DictEntryIO &entry)
  {
    return { entry.english, entry.russian };
  }

  std::istream &operator>>(std::istream &istream, DictEntryIO &entry)
  {
    using inputIterator = std::istream_iterator< std::string >;
    std::istream::sentry sentry(istream);

    if (!sentry) {
      return istream;
    }

    size_t entry_count = 0;
    istream >> entry_count;

    if (!istream || entry_count < 1) {
      istream.setstate(std::ios::failbit);
      return istream;
    }

    std::string english;
    istream >> english;

    if (!istream) {
      return istream;
    }

    std::vector< std::string > russian;
    russian.reserve(entry_count);
    auto inserter = std::back_inserter(russian);
    std::copy_n(inputIterator(istream), entry_count, inserter);

    if (istream) {
      entry = { english, russian };
    }

    return istream;
  }

  std::istream &operator>>(std::istream &istream, er_dictionary &dict)
  {
    using inputIterator = std::istream_iterator< DictEntryIO >;
    std::istream::sentry sentry(istream);

    if (!sentry) {
      return istream;
    }

    size_t entry_count = 0;
    istream >> entry_count;

    if (!istream) {
      return istream;
    }

    std::vector< DictEntryIO > entries;
    entries.reserve(entry_count);
    auto inserter = std::back_inserter(entries);
    std::copy_n(inputIterator(istream), entry_count, inserter);

    if (!istream) {
      return istream;
    }

    er_dictionary dictionary;
    auto dictInserter = std::inserter(dictionary, dictionary.end());
    auto begin = entries.cbegin();
    auto end = entries.cend();

    std::transform(begin, end, dictInserter, transformEntryToPair);
    std::swap(dict, dictionary);
    return istream;
  }

  std::ostream &operator<<(std::ostream &ostream, const DictEntryIO &entry)
  {
    std::ostream::sentry sentry(ostream);

    if (!sentry) {
      return ostream;
    }

    ostream << entry.russian.size() << ' ' << entry.english << ' ';
    auto output = std::ostream_iterator< std::string >(ostream, " ");
    std::copy(entry.russian.cbegin(), entry.russian.cend(), output);

    return ostream;
  }

  std::ostream &operator<<(std::ostream &ostream, const er_dictionary &dict)
  {
    std::ostream::sentry sentry(ostream);

    if (!sentry) {
      return ostream;
    }

    ostream << dict.size() << '\n';
    auto output = std::ostream_iterator< entry >(ostream, "\n");
    std::transform(dict.cbegin(), dict.cend(), output, transformPairToEntry);

    return ostream;
  }
}
