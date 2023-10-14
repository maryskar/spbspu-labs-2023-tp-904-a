#include "Graph.h"
#include <algorithm>
#include <functional>
#include <limits>
#include <exception>
#include <iterator>
#include <set>
#include <cmath>
#include <queue>

void avdeeva::Graph::setData()
{
  distances.resize(verts.size());
  previous.resize(verts.size());
  std::fill_n(distances.begin(), verts.size(), std::numeric_limits< int >::max());
  std::fill_n(previous.begin(), verts.size(), "0");
  path.clear();
}
bool avdeeva::Graph::checkNode(const std::string & vertName)
{
  return std::find(verts.begin(), verts.end(), vertName) != verts.end();
}
bool avdeeva::Graph::checkNodes()
{
  using namespace std::placeholders;
  auto pred = std::bind(std::not_equal_to<>(), 0, _1);
  return std::all_of(values.begin(), values.end(), pred);
}
size_t avdeeva::Graph::getIndexVert(const std::string & element)
{
  if (!checkNode(vertName))
  {
    throw std::logic_error("There is no vertex with this name");
  }
  auto iter = std::find(verts.begin(), verts.end(), element);
  size_t i = std::distance(verts.begin(), iter);
  return i;
}
bool avdeeva::Graph::checkSignValues()
{
  using namespace std::placeholders;
  auto pred = std::bind(std::greater_equal<>(), 0, _1);
  return std::all_of(values.begin(), values.end(), pred);
}
void avdeeva::Graph::insertVert(const std::string & vertFrom, const std::string & vertTo, int value)
{
  std::vector< int > newValues;
  if (vertFrom == vertTo)
  {
    throw std::logic_error("Vertex will connected to itself");
  }
  if (values.empty())
  {
    values.resize(4);
    std::fill(values.begin(), values.end(), 0);
    verts.push_back(vertFrom);
    verts.push_back(vertTo);
  }
  else if (!checkNode(vertTo) || !checkNode(vertFrom))
  {
    size_t n = verts.size();
    auto beginIt = values.begin();
    auto endIt = beginIt + n;
    if (!checkNode(vertFrom) && (checkNode(vertTo)) || !checkNode(vertTo) && checkNode(vertFrom))
    {
      newValues.reserve((verts.size() + 1) * (verts.size() + 1));
      for (size_t i = 0; i < verts.size(); ++i)
      {
        std::copy(beginIt, endIt, std::back_inserter(newValues));
        newValues.push_back(0);
        beginIt = endIt;
        endIt = endIt + n;
      }
      for (size_t i = 0; i < verts.size() + 1; ++i)
      {
        newValues.push_back(0);
      }
      !checkNode(vertFrom) ? verts.push_back(vertFrom) : verts.push_back(vertTo);
    }
    else if (!checkNode(vertTo) && !checkNode(vertFrom))
    {
      newValues.reserve((verts.size() + 2) * (verts.size() + 2));
      for (size_t i = 0; i < verts.size(); ++i)
      {
        std::copy(beginIt, endIt, std::back_inserter(newValues));
        newValues.push_back(0);
        newValues.push_back(0);
        beginIt = endIt;
        endIt = endIt + n;
      }
      for (size_t i = 0; i < 2 * (verts.size() + 2); ++i)
      {
        newValues.push_back(0);
      }
      verts.push_back(vertFrom);
      verts.push_back(vertTo);
    }
    values.swap(newValues);
  }
  size_t i = getIndexVert(vertFrom);
  size_t j = getIndexVert(vertTo);
  size_t cols = verts.size();
  values[i * cols + j] = value;
}
void avdeeva::Graph::renameVert(const std::string & vertName, const std::string & vertNewName)
{
  size_t i = getIndexVert(vertName);
  verts[i] = vertNewName;
}
bool avdeeva::Graph::checkArc(const std::string & vertFrom, const std::string &  vertTo)
{
  size_t i = getIndexVert(vertFrom);
  size_t j = getIndexVert(vertTo);
  size_t cols = verts.size();
  return values[i * cols + j];
}
void avdeeva::Graph::deleteVert(std::string & vertName)
{
  size_t size = verts.size();
  size_t i = getIndexVert(vertName);
  std::vector< int > newValues;
  for (auto it = values.begin(); it != values.end(); ++it)
  {
    auto elementRow = std::distance(values.begin(), it) / size;
    auto elementColumn = std::distance(values.begin(), it) % size;
    if (elementRow != i && elementColumn != i)
    {
      newValues.push_back(*it);
    }
  }
  auto newEnd = std::remove(verts.begin(), verts.end(), vertName);
  verts.erase(newEnd, verts.end());
  values.swap(newValues);
}
void avdeeva::Graph::printMatrix(std::ostream & out)
{
  size_t graphSize = verts.size();
  out << "  ";
  std::copy(verts.begin(), verts.end(), std::ostream_iterator< std::string >(out, " "));
  out << std::endl;
  for (size_t i = 0; i < graphSize; ++i)
  {
    out << verts[i] << " ";
    for (size_t j = 0; j < graphSize; ++j)
    {
      out << values[i * graphSize + j] << " ";
    }
    out << std::endl;
  }
}
void avdeeva::Graph::printList(std::ostream & out)
{
  size_t graphSize = verts.size();
  for (size_t i = 0; i < graphSize; ++i)
  {
    for (size_t j = 0; j < graphSize; ++j)
    {
      if (checkArc(verts[i], verts[j]))
      {
        out << verts[i] << " - " << verts[j] << ": " << values[i * graphSize + j];
        out << std::endl;
      }
    }
  }
}
bool avdeeva::Graph::checkSimilarVerts(const Graph & other)
{
  std::set< std::string > set(verts.begin(), verts.end());
  std::set< std::string > setOther(other.verts.begin(), other.verts.end());
  std::vector< std::string > common;
  auto beginSet = set.begin();
  auto endSet = set.end();
  auto beginOtherSet = setOther.begin();
  auto endOtherSet = setOther.end();
  auto ins = std::inserter(common, common.begin());
  std::set_intersection(beginSet, endSet, beginOtherSet, endOtherSet, ins);
  return !common.empty();
}
void avdeeva::Graph::getUnion(Graph & lhs, const std::string & vlhs, Graph & rhs, const std::string & vrhs, int value)
{
  if (lhs.checkSimilarVerts(rhs))
  {
    throw std::invalid_argument("There are similar vertexes in graphs. Use command RENAME");
  }
  size_t lhsSize = lhs.verts.size();
  size_t rhsSize = rhs.verts.size();
  values.reserve(std::pow(lhsSize + rhsSize, 2));
  auto beginIt = lhs.values.begin();
  auto endIt = beginIt + lhsSize;
  for (size_t i = 0; i < lhsSize; ++i)
  {
    std::copy(beginIt, endIt, std::back_inserter(values));
    for (size_t j = 0; j < rhsSize; ++j)
    {
      values.push_back(0);
    }
    beginIt = endIt;
    endIt = endIt + rhsSize;
  }
  beginIt = rhs.values.begin();
  endIt = beginIt + rhsSize;
  for (size_t i = 0; i < rhsSize; ++i)
  {
    for (size_t j = 0; j < lhsSize; ++j)
    {
      values.push_back(0);
    }
    std::copy(beginIt, endIt, std::back_inserter(values));
    beginIt = endIt;
    endIt = endIt + rhsSize;
  }
  std::copy(lhs.verts.begin(), lhs.verts.end(), std::back_inserter(verts));
  std::copy(rhs.verts.begin(), rhs.verts.end(), std::back_inserter(verts));
  size_t i = getIndexVert(vlhs);
  size_t j = getIndexVert(vrhs);
  size_t cols = lhsSize + rhsSize;
  values[i * cols + j] = value;
}
void avdeeva::Graph::restorePath(const std::string & start, const std::string & end)
{
  if (distances[getIndexVert(end)] != std::numeric_limits<int>::max())
  {
    std::string currentVertex = end;
    while (currentVertex != start)
    {
      path.push_back(currentVertex);
      currentVertex = previous[getIndexVert(currentVertex)];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
  }
}
void avdeeva::Graph::dijkstra(const std::string & start, const std::string & end, std::ostream & out)
{
  if (checkSignValues())
  {
    throw std::logic_error("DIJKSTRA works only with non-negative weights of Graph");
  }
  setData();
  size_t graphSize = verts.size();
  std::priority_queue< std::pair< int, std::string >, std::vector< std::pair< int, std::string > >, std::greater< std::pair< int, std::string > > > pq;
  distances[getIndexVert(start)] = 0;
  pq.push(std::make_pair(0, start));
  while (!pq.empty())
  {
    std::string currentVert = pq.top().second;
    int currentDist = pq.top().first;
    pq.pop();
    if (currentDist > distances[getIndexVert(currentVert)])
    {
      continue;
    }
    for (int i = 0; i < graphSize; i++)
    {
      int weight = values[getIndexVert(currentVert) * graphSize + i];
      if (weight != 0 && distances[getIndexVert(currentVert)] + weight < distances[i])
      {
        distances[i] = distances[getIndexVert(currentVert)] + weight;
        previous[i] = currentVert;
        pq.push(std::make_pair(distances[i], verts[i]));
      }
    }
  }
  restorePath(start, end);
  printPath(start ,end, out);
}
void avdeeva::Graph::printPath(const std::string & start, const std::string & end, std::ostream & out)
{
  if (path.empty())
  {
    std::cout << "Way from  " << start << " to " << end << " is not exist " << '\n';
  }
  else
  {
    out << "Shortest way from  " << start << " to " << end << ": " << '\n';
    std::copy(path.begin(), path.end(), std::ostream_iterator< std::string >(out, " "));
    out << '\n';
  }
}
void avdeeva::Graph::bellmanFord(const std::string & start, const std::string & end, std::ostream & out)
{
  setData();
  const int inf = std::numeric_limits<int>::max();
  size_t graphSize = verts.size();
  distances[getIndexVert(start)] = 0;
  for (int i = 0; i < graphSize - 1; i++)
  {
    for (int j = 0; j < graphSize; j++)
    {
      for (int k = 0; k < graphSize; k++)
      {
        int weight = values[j * graphSize + k];
        if (weight != 0 && distances[j] != inf && distances[j] + weight < distances[k])
        {
          distances[k] = distances[j] + weight;
          previous[k] = verts[j];
        }
      }
    }
  }
  for (int j = 0; j < graphSize; j++)
  {
    for (int k = 0; k < graphSize; k++)
    {
      int weight = values[j * graphSize + k];
      if (weight != 0 && distances[j] != inf && distances[j] + weight < distances[k])
      {
        throw std::logic_error("Graph has cycles of negative weight");
      }
    }
  }
  restorePath(start, end);
  printPath(start ,end, out);
}
void avdeeva::Graph::waveAlgorithm(const std::string & start, const std::string & end, std::ostream & out)
{
  setData();
  size_t graphSize = verts.size();
  distances[getIndexVert(start)] = 0;
  std::queue< size_t > wave_queue;
  wave_queue.push(getIndexVert(start));
  distances[getIndexVert(start)] = 0;
  while (!wave_queue.empty())
  {
    size_t current = wave_queue.front();
    wave_queue.pop();
    if (current == getIndexVert(end))
    {
      break;
    }
    for (int i = 0; i < graphSize; i++)
    {
      int weight = values[current * graphSize + i];
      if (weight > 0 && distances[current] + weight < distances[i])
      {
        distances[i] = distances[current] + weight;
        previous[i] = verts[current];
        wave_queue.push(i);
      }
    }
  }
  restorePath(start, end);
  printPath(start ,end, out);
}
