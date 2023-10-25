#include "Graph.h"
#include <iostream>

namespace nesterov
{
  bool Graph::hasVertex(int vertex)
  {
    return list.find(vertex) != list.end();
  }

  bool Graph::hasEdge(int v1, int v2)
  {
    if (!hasVertex(v1) || !hasVertex(v2))
    {
      throw std::logic_error("");
    }
    return list[v1].count(v2) > 0;
  }

  void Graph::addVertex(int vertex)
  {
    if (hasVertex(vertex))
    {
      throw std::logic_error("");
    }
    list[vertex] = std::set< int >();
  }

  void Graph::removeVertex(int vertex)
  {
    if (isVertexInUse(vertex))
    {
      throw std::logic_error("");
    }
    list.erase(vertex);
  }

  bool Graph::isVertexInUse(int vertex)
  {
    return std::find_if(
      list.begin(),
      list.end(),
      std::bind(isVertexInUseHelper, std::placeholders::_1, vertex)
    ) != list.end();
  }

  bool Graph::isVertexInUseHelper(const std::pair< int, std::set< int > > &pair, int vertex)
  {
    return pair.second.count(vertex) > 0 || (pair.first == vertex && !pair.second.empty());
  }

  Graph::~Graph() = default;
}
