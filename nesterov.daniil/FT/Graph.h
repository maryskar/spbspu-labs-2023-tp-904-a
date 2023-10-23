#ifndef FT_GRAPH_H
#define FT_GRAPH_H

#include <vector>
#include <set>
#include <map>

namespace nesterov
{
  class Graph
  {
  public:
    void addVertex(int vertex);
    virtual void addEdge(int v1, int v2) = 0;
    virtual void removeEdge(int v1, int v2) = 0;
    void removeVertex(int vertex);
    bool hasVertex(int vertex);
    bool hasEdge(int v1, int v2);
    virtual ~Graph();
  protected:
    std::map< int, std::set< int > > list;
  private:
    bool isVertexInUse(int vertex);
    static bool isVertexInUseHelper(const std::pair< int, std::set< int > > &pair, int vertex);
  };

}

#endif
