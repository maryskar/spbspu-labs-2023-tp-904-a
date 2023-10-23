#include "DirectedGraph.h"
#include <algorithm>
#include <iostream>
#include <list>

namespace nesterov
{
  void DirectedGraph::addEdge(int v1, int v2)
  {
    if (!hasVertex(v1) || !hasVertex(v2))
    {
      throw std::logic_error("");
    }
    list[v1].insert(v2);
  }

  void DirectedGraph::removeEdge(int v1, int v2)
  {
    if (!hasEdge(v1, v2))
    {
      throw std::logic_error("");
    }
    list[v1].erase(v2);
  }

  void DirectedGraph::dfs(int vertex, std::ostream &out)
  {
    if (!hasVertex(vertex))
    {
      throw std::logic_error("");
    }
    std::set< int > visited;
    std::vector< int > stack;

    stack.push_back(vertex);

    while (!stack.empty())
    {
      int s = stack.back();
      stack.pop_back();

      if (visited.find(s) == visited.end())
      {
        out << s << " ";
        visited.insert(s);
      }

      std::copy_if(
        list[s].begin(),
        list[s].end(),
        std::back_inserter(stack),
        std::bind(isVisited, std::placeholders::_1, visited)
      );
    }

    out << '\n';
  }

  void DirectedGraph::topologicalSortUtil(int vertex, std::set< int > &visited, std::vector< int > &stack)
  {
    visited.insert(vertex);

    for (int v: list[vertex])
      if (!isVisited(vertex, visited))
        topologicalSortUtil(v, visited, stack);

    stack.push_back(vertex);
  }

  void DirectedGraph::topologicalSort()
  {
    std::vector< int > stack;
    std::set< int > visited;

    for (const auto &i: list)
      if (!isVisited(i.first, visited))
        topologicalSortUtil(i.first, visited, stack);

    std::copy(
      stack.rbegin(),
      stack.rend(),
      std::ostream_iterator<int>(std::cout, " ")
    );

    std::cout << '\n';
  }

  bool DirectedGraph::isVisited(int vertex, std::set< int > &visited) {
    return visited.find(vertex) != visited.end();
  }
}
