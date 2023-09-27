#ifndef COMPORATOR_HPP
#define COMPORATOR_HPP

#include <utility>
#include "data-types.hpp"

namespace turkin
{
  struct SortByFreq
  {
    bool operator()(const std::pair< char, node_t * > & lhs, const std::pair< char, node_t * > rhs);
  };

  struct StrCount
  {
    public:
      explicit StrCount(char let);
      bool operator()(const char rhs);
    private:
      char let_;
  };

  struct CopyCode
  {
    public:
      explicit CopyCode(encoding_map_t map);
      encoding_t operator()(encoding_t lhs, const char rhs);
    private:
      encoding_map_t map_;
  };
}

#endif
