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
    size_t getVertsSize();
    std::vector < int > getValues();
    std::vector < std::string > getVerts();
    size_t getIndexVert(const std::string & element);
    bool checkPositiveValues();
    bool checkNode(const std::string & vertName);
    bool checkNodes();
    bool checkArc(const std::string &  vertFrom, const std::string &  vertTo);
    void insertVert(const std::string & vertFrom, const std::string & vertTo, int value);
    void deleteVert(std::string & vertName);
    void renameVert(const std::string & vertName, const std::string & vertNewName);
    void getUnion(Graph & lhs, const std::string & vlhs, Graph & rhs, const std::string & vrhs, int value);
    void printMatrix(std::ostream & out);
    void printList(std::ostream & out);
  private:
    bool checkSimilarVerts(const Graph & other);
    std::vector< std::string > verts;
    std::vector< int > values;
  };
}

#endif
