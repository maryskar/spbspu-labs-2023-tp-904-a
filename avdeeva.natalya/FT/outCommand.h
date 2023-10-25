#ifndef SPBSPU_LABS_2023_TP_904_A_OUTCOMMAND_H
#define SPBSPU_LABS_2023_TP_904_A_OUTCOMMAND_H

#include <string>
#include <map>
#include "Graph.h"

namespace avdeeva
{
  void createGraphCommand(std::map< std::string, avdeeva::Graph > & graphs, std::istream & in, std::ostream & out);
  void checkNodesCommand(std::map< std::string, avdeeva::Graph > & graphs, std::istream & in, std::ostream & out);
  void checkNodeCommand(std::map< std::string, avdeeva::Graph > & graphs, std::istream & in, std::ostream & out);
  void checkArcCommand(std::map< std::string, avdeeva::Graph > & graphs, std::istream & in, std::ostream & out);
  void insertVertCommand(std::map< std::string, avdeeva::Graph > & graphs, std::istream & in, std::ostream & out);
  void renameVertCommand(std::map< std::string, avdeeva::Graph > & graphs, std::istream & in, std::ostream & out);
  void deleteVertCommand(std::map< std::string, avdeeva::Graph > & graphs, std::istream & in, std::ostream & out);
  void dijkstraCommand(std::map< std::string, avdeeva::Graph > & graphs, std::istream & in, std::ostream & out);
  void bellmanFordCommand(std::map< std::string, avdeeva::Graph > & graphs, std::istream & in, std::ostream & out);
  void waveAlgCommand(std::map< std::string, avdeeva::Graph > & graphs, std::istream & in, std::ostream & out);
  void printMatrixCommand(std::map< std::string, avdeeva::Graph > & graphs, std::istream & in, std::ostream & out);
  void printListCommand(std::map< std::string, avdeeva::Graph > & graphs, std::istream & in, std::ostream & out);
  void getUnionCommand(std::map< std::string, avdeeva::Graph > & graphs, std::istream & in, std::ostream & out);
  void helpCommand(std::ostream & out);
}

#endif
