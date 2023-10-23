#ifndef FT_UNDIRECTEDGRAPH_H
#define FT_UNDIRECTEDGRAPH_H

#include "Graph.h"

namespace nesterov
{
  class UndirectedGraph : public Graph
  {
  public:
    void addEdge(int v1, int v2) override;
    void removeEdge(int v1, int v2) override;
  };
}

#endif
