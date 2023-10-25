#ifndef FT_ORIENTEDGRAPH_H
#define FT_ORIENTEDGRAPH_H

#include <stack>
#include "Graph.h"

namespace nesterov
{
  class OrientedGraph: public Graph
  {
  public:
    void addEdge(int v1, int v2) override;
    void removeEdge(int v1, int v2) override;
    void dfs(int vertex, std::ostream &out);
    void topologicalSort();
  private:
    std::map< int, int > indegree;
    void topologicalSortUtil(std::set< int > &visited, std::vector< int > &stack);
    static bool isVisited(int vertex, std::set< int > &visited);
    void increaseIndegree(int vertex);
    void decreaseIndegree(int vertex);
  };
}

#endif
