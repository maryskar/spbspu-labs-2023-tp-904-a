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
    friend std::ostream &operator<<(std::ostream &out, const Graph &graph);
  protected:
    std::map< int, std::set< int > > list;
  private:
    static void printGraphPair(const std::pair< int, std::set< int > > &pair, std::ostream &out);
    bool isVertexInUse(int vertex);
    static bool isVertexInUseHelper(const std::pair< int, std::set< int > > &pair, int vertex);
  };

}

#endif
