#include <iostream>
#include "DirectedGraph.h"
#include "UndirectedGraph.h"
#include "CommandHandler.h"
#include "Graph.h"

void skipUntilNewLine(std::istream &in);

int main()
{
  using namespace nesterov;

  std::unordered_map< std::string, std::shared_ptr< Graph > > graphs;
  graphs["graph1"] = std::make_shared< DirectedGraph >();
  graphs["graph2"] = std::make_shared< UndirectedGraph >();
  graphs["graph3"] = std::make_shared< DirectedGraph >();
  graphs["graph4"] = std::make_shared< DirectedGraph >();

  std::for_each(graphs.begin(), graphs.end(), [&](const auto &graph)
  {
    if (auto directed = std::dynamic_pointer_cast< DirectedGraph >(graph.second))
    {
      std::cout << "Directed\n";
      directed->addVertex(2);
      directed->addVertex(4);
      directed->addEdge(4, 2);
    }
    else if (auto undirected = std::dynamic_pointer_cast< UndirectedGraph >(graph.second))
    {
      std::cout << "Undirected\n";
      undirected->addVertex(1);
      undirected->addVertex(5);
      undirected->addEdge(5, 1);
    }

    std::cout << *graph.second;
  });

  std::map< std::string, base_cmd_t > base_cmds{
    {"HELP", executeHelpCommand},
  };

  std::map< std::string, const_cmd_t > const_cmds{
    {"EXISTS_VERTEX", executeExistsVertexCommand},
    {"EXISTS_ARC", executeExistsArcCommand},
    {"DFS", executeDfsCommand},
    {"SORT", executeSortCommand}
  };

  std::map< std::string, cmd_t > cmds{
    {"CREATE", executeCreateCommand},
    {"DELETE", executeDeleteCommand},
    {"ADD_VERTEX", executeAddVertexCommand},
    {"REMOVE_VERTEX", executeRemoveVertexCommand},
    {"ADD_ARC", executeAddArcCommand},
    {"REMOVE_ARC", executeRemoveArcCommand}
  };

  std::istream &cmdinput = std::cin;
  while (!cmdinput.eof())
  {
    std::string cmd;
    cmdinput >> cmd;
    if (cmd.empty())
    {
      continue;
    }

    try
    {
      try
      {
        auto toexecute = base_cmds.at(cmd);
        toexecute(std::cout);
      } catch (...)
      {
        try
        {
          auto toexecute = const_cmds.at(cmd);
          toexecute(graphs, cmdinput, std::cout, std::cerr);
        } catch (...)
        {
          auto toexecute = cmds.at(cmd);
          toexecute(graphs, cmdinput, std::cout, std::cerr);
        }
      }
    } catch (...)
    {
      cmdinput.clear();
      skipUntilNewLine(cmdinput);
      std::cout << "<INVALID COMMAND>\n";
    }
  }
  return 0;
}

void skipUntilNewLine(std::istream &in)
{
  auto maxstream = std::numeric_limits< std::streamsize >::max();
  in.ignore(maxstream, '\n');
}