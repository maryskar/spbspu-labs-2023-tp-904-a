#ifndef SPBSPU_LABS_2023_TP_904_A_SOLUTION_H
#define SPBSPU_LABS_2023_TP_904_A_SOLUTION_H

#include "Graph.h"

namespace avdeeva {
  class Solution
  {
  public:
    Solution(Graph graph);
    void restorePath(const std::string & start, const std::string & end);
    void printPath(const std::string & start, const std::string & end, std::ostream & out);
    void dijkstra(const std::string & start, const std::string & end, std::ostream & out);
    void bellmanFord(const std::string & start, const std::string & end, std::ostream & out);
    void waveAlg(const std::string & start, const std::string & end, std::ostream & out);
  private:
    Graph graph;
    std::vector< int > gValues;
    std::vector< std::string > gVerts;
    std::vector< int > distances;
    std::vector< std::string > previous;
    std::vector< std::string > path;
  };
}

#endif
