#ifndef CONVERINFIXTOPOSTFIX_HPP
#define CONVERINFIXTOPOSTFIX_HPP
#include <string>
#include <queue>
#include <map>

namespace hrushchev
{
  std::queue< std::string > convertInfixToPostfix(std::queue< std::string >& infixQueue,
    std::map< std::string, std::string >& variables);
}

#endif

