#ifndef MASHKIN_ANDREW_SEMANTICTREE_H
#define MASHKIN_ANDREW_SEMANTICTREE_H
#include <map>
#include <string>

namespace mashkin
{
  template< class T >
  struct SemanticTree
  {
    T data;
    std::map< short int, SemanticTree< T >* > children;
  };
}
#endif
