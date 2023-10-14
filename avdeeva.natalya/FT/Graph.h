#ifndef SPBSPU_LABS_2023_TP_904_A_GRAPH_H
#define SPBSPU_LABS_2023_TP_904_A_GRAPH_H

#include <string>
#include <iostream>
#include <vector>

namespace avdeeva
{
  class Graph
  {
  public:
    bool checkNodes();
    bool checkNode(const std::string & vertName);
    bool checkArc(const std::string &  vertFrom, const std::string &  vertTo);
    void insertVert(const std::string & vertFrom, const std::string & vertTo, int value);
    void deleteVert(std::string & vertName);
    void renameVert(const std::string & vertName, const std::string & vertNewName);
    void dijkstra(const std::string & start, const std::string & end, std::ostream & out);
    void bellmanFord(const std::string & start, const std::string & end, std::ostream & out);
    void waveAlgorithm(const std::string & start, const std::string & end, std::ostream & out);
    void getUnion(Graph & lhs, const std::string & vlhs, Graph & rhs, const std::string & vrhs, int value);
    void printMatrix(std::ostream & out);
    void printList(std::ostream & out);
  private:
    size_t getIndexVert(const std::string & element);
    void setData();
    bool checkSimilarVerts(const Graph & other);
    bool checkSignValues();
    void restorePath(const std::string & start, const std::string & end);
    void printPath(const std::string & start, const std::string & end, std::ostream & out);
    std::vector< std::string > verts;
    std::vector< int > values;
    std::vector< int > distances;
    std::vector< std::string > previous;
    std::vector< std::string > path;
  };
}

#endif
