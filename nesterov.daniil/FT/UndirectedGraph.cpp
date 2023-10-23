#include "UndirectedGraph.h"

namespace nesterov
{
  void UndirectedGraph::addEdge(int v1, int v2)
  {
    if (!hasVertex(v1) || !hasVertex(v2))
    {
      throw std::logic_error("");
    }
    list[v1].insert(v2);
    list[v2].insert(v1);
  }

  void UndirectedGraph::removeEdge(int v1, int v2)
  {
    if (!hasEdge(v1, v2))
    {
      throw std::logic_error("");
    }
    list[v1].erase(v2);
    list[v2].erase(v1);
  }
}
