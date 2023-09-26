#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <memory>

namespace turkin
{
  template< typename T >
  struct TreeNode
  {
    using t_node = std::shared_ptr< TreeNode< T > >;
    TreeNode():
      data(T()),
      parent(),
      left(),
      right()
    {}
    
    explicit TreeNode(T dt):
      data(dt),
      parent(),
      left(),
      right()
    {}
    
    explicit TreeNode(T dt, t_node lhs, t_node rhs):
      data(dt),
      parent(),
      left(lhs),
      right(rhs)
    {}
    
    T data;
    t_node parent;
    t_node left;
    t_node right;
    int height;
  };
}

#endif
