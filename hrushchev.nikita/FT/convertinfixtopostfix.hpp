#ifndef CONVERINFIXTOPOSTFIX_HPP
#define CONVERINFIXTOPOSTFIX_HPP
#include <string>
#include <avltree.hpp>
#include <queue>

namespace hrushchev
{
  std::queue< std::string > convertInfixToPostfix(std::queue< std::string >& infixQueue,
    AVLTree< std::string, std::string >& variables);
}

#endif

