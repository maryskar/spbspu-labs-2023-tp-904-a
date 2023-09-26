#ifndef COMPORATOR_HPP
#define COMPORATOR_HPP

#include <utility>
#include "data-types.hpp"

namespace turkin
{
  struct SortByFreq
  {
    using t_node = std::shared_ptr< node_t >;
    bool operator()(const std::pair< char, t_node > & lhs, const std::pair< char, t_node > rhs);
  };
}

#endif
