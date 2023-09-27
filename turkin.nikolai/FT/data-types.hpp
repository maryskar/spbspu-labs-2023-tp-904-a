#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

#include <string>
#include <map>
#include <queue>
#include <memory>

#include "tree-node.hpp"

namespace turkin
{
  using phrase_t = std::string;
  using encoding_t = std::string;
  using encoding_pair_t = std::pair< char, std::size_t >;
  using encoding_map_t = std::map< char, encoding_t, std::less< > >;
  using node_t = TreeNode< encoding_pair_t >;
  using encoding_list_t = std::map< char, node_t *, std::less< > >;
  using queue_t = std::queue< node_t * >;
}

#endif
