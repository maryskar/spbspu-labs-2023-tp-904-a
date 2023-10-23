#include "CommandHandler.h"
#include <string>
#include <iostream>
#include "DirectedGraph.h"
#include "UndirectedGraph.h"

namespace nesterov
{
  void executeExistsVertexCommand(const graphsMap &map, std::istream &in, std::ostream &out, std::ostream &)
  {
    std::string graphName;
    int vertex = 0;
    if (in >> graphName >> vertex)
    {
      const auto &graph = map.at(graphName);
      if (graph->hasVertex(vertex))
      {
        out << "TRUE\n";
      }
      else
      {
        out << "FALSE\n";
      }
    }
    else
    {
      throw std::logic_error("");
    }
  }

  void executeExistsArcCommand(const graphsMap &map, std::istream &in, std::ostream &out, std::ostream &)
  {
    std::string graphName;
    int vertex1 = 0;
    int vertex2 = 0;
    if (in >> graphName >> vertex1 >> vertex2)
    {
      const auto &graph = map.at(graphName);
      if (graph->hasEdge(vertex1, vertex2))
      {
        out << "TRUE\n";
      }
      else
      {
        out << "FALSE\n";
      }
    }
    else
    {
      throw std::logic_error("");
    }
  }

  void executeDfsCommand(const graphsMap &map, std::istream &in, std::ostream &out, std::ostream &err)
  {
    std::string graphName;
    int vertex = 0;
    if (in >> graphName >> vertex)
    {
      const auto &graph = map.at(graphName);
      if (auto directedGraph = std::dynamic_pointer_cast< DirectedGraph >(graph))
      {
        directedGraph->dfs(vertex, out);
      }
      else
      {
        throw std::logic_error("");
      }
    }
    else
    {
      throw std::logic_error("");
    }
  }

  void executeSortCommand(const graphsMap &map, std::istream &in, std::ostream &out, std::ostream &err)
  {
    std::string graphName;

    if(in >> graphName)
    {
      const auto &graph = map.at(graphName);
      if (auto directedGraph = std::dynamic_pointer_cast< DirectedGraph >(graph))
      {
        directedGraph->topologicalSort();
      }
      else
      {
        throw std::logic_error("");
      }
    }
    else
    {
      throw std::logic_error("");
    }
  }

  void executeCreateCommand(graphsMap &map, std::istream &in, std::ostream &, std::ostream &)
  {
    std::string graphType;
    std::string graphName;
    if (in >> graphType >> graphName)
    {
      if (map.count(graphName) != 0)
      {
        throw std::logic_error("");
      }

      if (graphType == "DIRECTED")
      {
        map[graphName] = std::make_shared< DirectedGraph >();
      }
      else if (graphType == "UNDIRECTED")
      {
        map[graphName] = std::make_shared< UndirectedGraph >();
      }
      else
      {
        throw std::logic_error("");
      }
    }
    else
    {
      throw std::logic_error("");
    }
  }

  void executeDeleteCommand(graphsMap &map, std::istream &in, std::ostream &, std::ostream &)
  {
    std::string graphName;
    if (in >> graphName)
    {
      bool erased = map.erase(graphName);
      if (!erased)
      {
        throw std::logic_error("");
      }
    }
    else
    {
      throw std::logic_error("");
    }
  }

  void executeAddVertexCommand(graphsMap &map, std::istream &in, std::ostream &, std::ostream &)
  {
    std::string graphName;
    int vertex = 0;
    if (in >> graphName >> vertex)
    {
      auto graph = map.at(graphName);
      graph->addVertex(vertex);
    }
    else
    {
      throw std::logic_error("");
    }
  }

  void executeRemoveVertexCommand(graphsMap &map, std::istream &in, std::ostream &, std::ostream &)
  {
    std::string graphName;
    int vertex = 0;
    if (in >> graphName >> vertex)
    {
      auto graph = map.at(graphName);
      graph->removeVertex(vertex);
    }
    else
    {
      throw std::logic_error("");
    }
  }

  void executeAddArcCommand(graphsMap &map, std::istream &in, std::ostream &, std::ostream &)
  {
    std::string graphName;
    int vertex1 = 0;
    int vertex2 = 0;
    if (in >> graphName >> vertex1 >> vertex2)
    {
      auto graph = map.at(graphName);
      graph->addEdge(vertex1, vertex2);
    }
    else
    {
      throw std::logic_error("");
    }
  }

  void executeRemoveArcCommand(graphsMap &map, std::istream &in, std::ostream &, std::ostream &)
  {
    std::string graphName;
    int vertex1 = 0;
    int vertex2 = 0;
    if (in >> graphName >> vertex1 >> vertex2)
    {
      auto graph = map.at(graphName);
      graph->removeEdge(vertex1, vertex2);
    }
    else
    {
      throw std::logic_error("");
    }
  }

  void executeHelpCommand(std::ostream &out)
  {
    out << "Топологическая сортировка. Обход в глубину.\n";
    out << "CREATE <DIRECTED/UNDIRECTED> <graph_name> - создать пустой"
      "ориентированный/неориентированный граф.\n";
    out << "DELETE <graph_name> - удалить граф.\n";
    out << "ADD_VERTEX <graph_name> <vertex> - добавить узел в граф.\n";
    out << "REMOVE_VERTEX <graph_name> <vertex> - удалить узел из графа.\n";
    out << "ADD_ARC <graph_name> <vertex> - добавить дугу между узлами.\n";
    out << "REMOVE_ARC <graph_name> <vertex> - удалить дугу между узлами.\n";
    out << "EXISTS_VERTEX <graph_name> <vertex> - проверить наличие узла.\n";
    out << "EXISTS_ARC <graph_name> <vertex> - проверить наличие дуги между узлами.\n";
    out << "DFS <graph_name> <vertex> - осуществить алгоритм поиска в глубину для заданного узла.\n";
    out << "SORT <graph_name> - осуществить топологическую сортировку.\n";
  }
}
