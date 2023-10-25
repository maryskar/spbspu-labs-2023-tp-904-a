#include "OrientedGraph.h"
#include <algorithm>
#include <iostream>
#include <list>

namespace nesterov
{
  void OrientedGraph::addEdge(int v1, int v2)
  {
    if (!hasVertex(v1) || !hasVertex(v2))
    {
      throw std::logic_error("");
    }
    list[v1].insert(v2);
    indegree[v2]++;
  }

  void OrientedGraph::removeEdge(int v1, int v2)
  {
    if (!hasEdge(v1, v2))
    {
      throw std::logic_error("");
    }
    list[v1].erase(v2);
    indegree[v2]--;
  }

  void OrientedGraph::dfs(int startVertex, std::ostream &out)
  {
    if (!hasVertex(startVertex))
    {
      throw std::logic_error("");
    }
    std::set< int > visited;
    std::vector< int > vertexes;

    vertexes.push_back(startVertex);

    while (!vertexes.empty())
    {
      int vertex = vertexes.back();
      vertexes.pop_back();

      if (!isVisited(vertex, visited))
      {
        out << vertex << " ";
        visited.insert(vertex);
      }

      std::copy_if(
        list[vertex].begin(),
        list[vertex].end(),
        std::back_inserter(vertexes),
        std::bind(std::logical_not< bool >(), std::bind(isVisited, std::placeholders::_1, visited))
      );
    }

    out << '\n';
  }

  void OrientedGraph::topologicalSortUtil(std::set< int > &visited, std::vector< int > &res)
  {
    bool vertexesLeft = false;

    for (const auto &pair: list)
    {
      int vertex = pair.first;
      if (indegree[vertex] == 0 && !isVisited(vertex, visited))
      {
        std::for_each(
          list[vertex].begin(),
          list[vertex].end(),
          std::bind(&OrientedGraph::decreaseIndegree, this, std::placeholders::_1)
        );

        res.push_back(vertex);
        visited.insert(vertex);
        topologicalSortUtil(visited, res);
        visited.erase(vertex);
        res.pop_back();

        std::for_each(
          list[vertex].begin(),
          list[vertex].end(),
          std::bind(&OrientedGraph::increaseIndegree, this, std::placeholders::_1)
        );

        vertexesLeft = true;
      }
    }

    if (!vertexesLeft)
    {
      std::copy(
        res.begin(),
        res.end(),
        std::ostream_iterator< int >(std::cout, " ")
      );
      std::cout << '\n';
    }
  }

  void OrientedGraph::topologicalSort()
  {
    std::vector< int > res;
    std::set< int > visited;
    topologicalSortUtil(visited, res);
  }

  bool OrientedGraph::isVisited(int vertex, std::set< int > &visited) {
    return visited.find(vertex) != visited.end();
  }

  void OrientedGraph::increaseIndegree(int vertex)
  {
    indegree[vertex]++;
  }

  void OrientedGraph::decreaseIndegree(int vertex)
  {
    indegree[vertex]--;
  }
}
