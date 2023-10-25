#ifndef FT_UNORIENTEDGRAPH_H
#define FT_UNORIENTEDGRAPH_H

#include "Graph.h"

namespace nesterov
{
  class UnorientedGraph: public Graph
  {
  public:
    void addEdge(int v1, int v2) override;
    void removeEdge(int v1, int v2) override;
  };
}

#endif
