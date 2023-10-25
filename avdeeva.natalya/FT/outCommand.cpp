#include "outCommand.h"
#include "Solution.h"

void avdeeva::createGraphCommand(std::map< std::string, avdeeva::Graph > & graphs,
    std::istream & in,
    std::ostream & out)
{
  std::string graphName;
  in >> graphName;
  if (!graphName.empty())
  {
    graphs.insert({graphName, avdeeva::Graph()});
  }
}
void avdeeva::checkNodesCommand(std::map< std::string, avdeeva::Graph > & graphs,
    std::istream & in,
    std::ostream & out)
{
  std::string graphName;
  in >> graphName;
  out << std::boolalpha << graphs.at(graphName).checkNodes() << '\n';
}
void avdeeva::checkNodeCommand(std::map< std::string, avdeeva::Graph > & graphs,
    std::istream & in,
    std::ostream & out)
{
  std::string graphName;
  std::string vertName;
  in >> graphName >> vertName;
  out << std::boolalpha << graphs.at(graphName).checkNode(vertName) << '\n';
}
void avdeeva::checkArcCommand(std::map< std::string, avdeeva::Graph > & graphs,
    std::istream & in,
    std::ostream & out)
{
  std::string graphName;
  std::string vertFrom;
  std::string vertTo;
  in >> graphName >> vertFrom >> vertTo;
  out << std::boolalpha << graphs.at(graphName).checkArc(vertFrom, vertTo) << '\n';
}
void avdeeva::insertVertCommand(std::map< std::string, avdeeva::Graph > & graphs,
    std::istream & in,
    std::ostream & out)
{
  std::string graphName;
  std::string vertFrom;
  std::string vertTo;
  int weight;
  in >> graphName >> vertFrom >> vertTo >> weight;
  graphs.at(graphName).insertVert(vertFrom, vertTo, weight);
}
void avdeeva::renameVertCommand(std::map< std::string, avdeeva::Graph > & graphs,
    std::istream & in,
    std::ostream & out)
{
  std::string graphName;
  std::string vertName;
  std::string vertNewName;
  in >> graphName >> vertName >> vertNewName;
  graphs.at(graphName).renameVert(vertName, vertNewName);
}
void avdeeva::deleteVertCommand(std::map< std::string, avdeeva::Graph > & graphs,
    std::istream & in,
    std::ostream & out)
{
  std::string graphName;
  std::string vertName;
  in >> graphName >> vertName;
  graphs.at(graphName).deleteVert(vertName);
}
void avdeeva::dijkstraCommand(std::map< std::string, avdeeva::Graph > & graphs,
    std::istream & in,
    std::ostream & out)
{
  std::string graphName;
  std::string vertFrom;
  std::string vertTo;
  in >> graphName >> vertFrom >> vertTo;
  Graph graph = graphs.at(graphName);
  Solution sol(graphs.at(graphName));
  sol.dijkstra(vertFrom, vertTo, out);
}
void avdeeva::bellmanFordCommand(std::map< std::string, avdeeva::Graph > & graphs,
    std::istream & in,
    std::ostream & out)
{
  std::string graphName;
  std::string vertFrom;
  std::string vertTo;
  in >> graphName >> vertFrom >> vertTo;
  Graph graph = graphs.at(graphName);
  Solution sol(graph);
  sol.bellmanFord(vertFrom, vertTo, out);
}
void avdeeva::waveAlgCommand(std::map< std::string, avdeeva::Graph > & graphs,
    std::istream & in,
    std::ostream & out)
{
  std::string graphName;
  std::string vertFrom;
  std::string vertTo;
  in >> graphName >> vertFrom >> vertTo;
  Graph graph = graphs.at(graphName);
  Solution sol(graph);
  sol.waveAlg(vertFrom, vertTo, out);
}
void avdeeva::printMatrixCommand(std::map< std::string, avdeeva::Graph  > & graphs,
    std::istream & in,
    std::ostream & out)
{
  std::string graphName;
  in >> graphName;
  graphs.at(graphName).printMatrix(out);
}
void avdeeva::printListCommand(std::map< std::string, avdeeva::Graph > & graphs,
    std::istream & in,
    std::ostream & out)
{
  std::string graphName;
  in >> graphName;
  graphs.at(graphName).printList(out);
}
void avdeeva::getUnionCommand(std::map< std::string, avdeeva::Graph > & graphs,
    std::istream & in,
    std::ostream & out)
{
  std::string graphName;
  std::string graphFirst;
  std::string graphSecond;
  std::string vertFrom;
  std::string vertTo;
  int weight;
  in >> graphName;
  if (!graphName.empty())
  {
    graphs.insert({graphName, avdeeva::Graph()});
  }
  in >> graphFirst >> vertFrom >> graphSecond >> vertTo >> weight;
  graphs.at(graphName).getUnion(graphs.at(graphFirst), vertFrom, graphs.at(graphSecond), vertTo, weight);
}
void avdeeva::helpCommand(std::ostream & out)
{
  out << "1. CREATE <graph_name> - forming an empty graph with the name graph_name" << '\n'
      << "2. INSERT <graph_name> <vert_from> <vert_to> <weight> - including a new node in the graph" << '\n'
      << "3. RENAME <graph_name> <vert_name> <vert_new_name> - renaming a graph vertex" << '\n'
      << "4. DELETE <graph_name> <vert_name> - excluding a node from a graph named name" << '\n'
      << "5. CHECK_NODES <graph_name> - checking for nodes in a graph named name" << '\n'
      << "6. CHECK_NODE <graph_name> <vert_name> - checking for the presence of a given node in the graph" << '\n'
      << "7. CHECK_ARC <graph_name> <vert_from> <vert_to> - " << '\n'
      << "checking for the presence of an arc between the specified nodes of the graph" << '\n'
      << "8. DIJKSTRA <graph_name> <vert_from> <vert_to> - finding the shortest path" << '\n'
      << "between a given pair of vertices of the graph name, edge weights are non-negative" << '\n'
      << "9. BELLMAN_FORD <graph_name> <vert_from> <vert_to> - " << '\n'
      << "finding the shortest path between a given pair of vertices of the graph name, "<< '\n'
      << "the weights of the edges can be negative" << '\n'
      << "10. WAVE <graph_name> <vert_from> <vert_to> - "<< '\n'
      << "finding the shortest path between a given pair of vertices of the graph name" << '\n'
      << "11. UNION <union_name> <graph_name1> <vert_from> <graph_name2> <vert_to> <weight>" << '\n'
      << "The UNION command creates a graph named union_name, which is the union " << '\n'
      << "of the vert_from vertex graphs of the first graph with the vert_to vertex of the second graph" << '\n'
      << "while preserving the existing edges of both vertices."<< '\n'
      << "Note that the names of the vertices in both graphs should not" << '\n'
      << "12. PRINT_LIST <graph_name> - output of the adjacency list (graph representation)" << '\n'
      << "Example of PRINT_LIST:" << '\n'
      << "A - B: 6" << '\n'
      << "A - C: 7" << '\n'
      << "C - B: 13" << '\n'
      << "13. PRINT_MATRIX <graph_name> - output of the adjacency matrix (graph representation)" << '\n'
      << "Example of PRINT_MATRIX with the same graph:" << '\n'
      << "   A   B   C" << '\n'
      << "A  0   6   7" << '\n'
      << "B  0   0   0" << '\n'
      << "C  0   13  0" << '\n'
      << "14. HELP - output of available commands" << '\n';
}
