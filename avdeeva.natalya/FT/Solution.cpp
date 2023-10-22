#include "Solution.h"
#include <queue>
#include <limits>
#include <algorithm>
#include <iterator>
namespace
{
  std::vector< int > initializeDistances(avdeeva::Graph g)
  {
    std::vector< int > result;
    size_t size = g.getVertsSize();
    result.resize(size);
    std::fill_n(result.begin(), size, std::numeric_limits< int >::max());
    return result;
  }
  std::vector< std::string > initializePrevious(avdeeva::Graph g)
  {
    std::vector< std::string > result;
    size_t size = g.getVertsSize();
    result.resize(size);
    std::fill_n(result.begin(), size, "0");
    return result;
  }
}
avdeeva::Solution::Solution(Graph g):
  graph(g),
  gValues(g.getValues()),
  gVerts(g.getVerts()),
  distances(initializeDistances(g)),
  previous(initializePrevious(g)),
  path()
{}

void avdeeva::Solution::restorePath(const std::string & start, const std::string & end)
{
  if (distances[graph.getIndexVert(end)] != std::numeric_limits< int >::max())
  {
    std::string currentVertex = end;
    while (currentVertex != start)
    {
      path.push_back(currentVertex);
      currentVertex = previous[graph.getIndexVert(currentVertex)];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
  }
}
void avdeeva::Solution::printPath(const std::string & start, const std::string & end, std::ostream & out)
{
  if (path.empty())
  {
    std::cout << "Way from " << start << "to " << end << "is not exist" << '\n';
  }
  else
  {
    out << "Shortest way from " << start << "to " << end << ": " << '\n';
    std::copy(path.begin(), path.end(), std::ostream_iterator< std::string >(out, " "));
    out << '\n';
  }
}
void avdeeva::Solution::dijkstra(const std::string & start, const std::string & end, std::ostream & out)
{
  if (graph.checkPositiveValues())
  {
    throw std::logic_error("DIJKSTRA works only with non-negative weights of Graph");
  }
  size_t graphSize = graph.getVertsSize();
  std::priority_queue< std::pair< int, std::string >,
    std::vector< std::pair< int, std::string > >,
    std::greater< std::pair< int, std::string > > > pq;
  distances[graph.getIndexVert(start)] = 0;
  pq.push(std::make_pair(0, start));
  while (!pq.empty())
  {
    std::string currentVert = pq.top().second;
    int currentDist = pq.top().first;
    pq.pop();
    if (currentDist > distances[graph.getIndexVert(currentVert)])
    {
      continue;
    }
    for (size_t i = 0; i < graphSize; i++)
    {
      int weight = gValues[graph.getIndexVert(currentVert) * graphSize + i];
      if (weight > 0 && distances[graph.getIndexVert(currentVert)] < distances[i] - weight)
      {
        distances[i] = distances[graph.getIndexVert(currentVert)] + weight;
        previous[i] = currentVert;
        pq.push(std::make_pair(distances[i], gVerts[i]));
      }
    }
  }
  restorePath(start, end);
  printPath(start ,end, out);
}
void avdeeva::Solution::bellmanFord(const std::string & start, const std::string & end, std::ostream & out)
{
  size_t graphSize = graph.getVertsSize();
  distances[graph.getIndexVert(start)] = 0;
  for (size_t i = 0; i < graphSize - 1; i++)
  {
    for (size_t j = 0; j < graphSize; j++)
    {
      for (size_t k = 0; k < graphSize; k++)
      {
        int weight = gValues[j * graphSize + k];
        if (weight != 0 && distances[j] != std::numeric_limits< int >::max() && distances[j] + weight < distances[k])
        {
          distances[k] = distances[j] + weight;
          previous[k] = gVerts[j];
        }
      }
    }
  }
  for (size_t j = 0; j < graphSize; j++)
  {
    for (size_t k = 0; k < graphSize; k++)
    {
      int weight = gValues[j * graphSize + k];
      if (weight != 0 && distances[j] != std::numeric_limits< int >::max() && distances[j] + weight < distances[k])
      {
        throw std::logic_error("Graph has cycles of negative weight");
      }
    }
  }
  restorePath(start, end);
  printPath(start ,end, out);
}
void avdeeva::Solution::waveAlg(const std::string & start, const std::string & end, std::ostream & out)
{
  if (graph.checkPositiveValues())
  {
    throw std::logic_error("WAVE Algorithm works only with non-negative weights of Graph");
  }
  size_t graphSize = graph.getVertsSize();
  distances[graph.getIndexVert(start)] = 0;
  std::queue< size_t > wave_queue;
  wave_queue.push(graph.getIndexVert(start));
  distances[graph.getIndexVert(start)] = 0;
  while (!wave_queue.empty())
  {
    size_t curr = wave_queue.front();
    wave_queue.pop();
    if (curr == graph.getIndexVert(end))
    {
      break;
    }
    for (size_t i = 0; i < graphSize; i++)
    {
      int weight = gValues[curr * graphSize + i];
      if (weight > 0 && distances[curr] < distances[i] - weight)
      {
        distances[i] = distances[curr] + weight;
        previous[i] = gVerts[curr];
        wave_queue.push(i);
      }
    }
  }
  restorePath(start, end);
  printPath(start, end, out);
}
