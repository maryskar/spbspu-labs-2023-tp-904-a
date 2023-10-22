#include "Graph.h"
#include <algorithm>
#include <functional>
#include <iterator>
#include <set>
#include <queue>

size_t avdeeva::Graph::getVertsSize()
{
  return verts.size();
}
std::vector< std::string > avdeeva::Graph::getVerts()
{
  return verts;
}
std::vector < int > avdeeva::Graph::getValues()
{
  return values;
}
size_t avdeeva::Graph::getIndexVert(const std::string & element)
{
  auto iter = std::find(verts.begin(), verts.end(), element);
  size_t i = std::distance(verts.begin(), iter);
  return i;
}
bool avdeeva::Graph::checkPositiveValues()
{
  using namespace std::placeholders;
  auto pred = std::bind(std::greater_equal<>(), 0, _1);
  return std::all_of(values.begin(), values.end(), pred);
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
      std::fill_n(std::back_inserter(newValues), verts.size() + 1, 0);
      !checkNode(vertFrom) ? verts.push_back(vertFrom) : verts.push_back(vertTo);
    }
    else if (!checkNode(vertTo) && !checkNode(vertFrom))
    {
      newValues.reserve((verts.size() + 2) * (verts.size() + 2));
      for (size_t i = 0; i < verts.size(); ++i)
      {
        std::copy(beginIt, endIt, std::back_inserter(newValues));
        std::fill_n(std::back_inserter(newValues), 2, 0);
        beginIt = endIt;
        endIt = endIt + n;
      }
      std::fill_n(std::back_inserter(newValues), 2 * (verts.size() + 2), 0);
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
  if (!checkNode(vertFrom) || !checkNode(vertTo))
  {
    throw std::logic_error("There are no such vertexes in graph");
  }
  size_t i = getIndexVert(vertFrom);
  size_t j = getIndexVert(vertTo);
  size_t cols = verts.size();
  return values[i * cols + j];
}
void avdeeva::Graph::deleteVert(std::string & vertName)
{
  if (!checkNode(vertName))
  {
    throw std::invalid_argument("There is no such vertex in graph");
  }
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
namespace
{
  void printRow(std::ostream &out, const std::string & vert, const std::vector< int > & row) {
    out << vert << " ";
    std::copy(row.begin(), row.end(), std::ostream_iterator< int >(out, " "));
    out << std::endl;
  }
}
void avdeeva::Graph::printMatrix(std::ostream & out)
{
  size_t graphSize = verts.size();
  out << "  ";
  std::copy(verts.begin(), verts.end(), std::ostream_iterator< std::string >(out, " "));
  out << std::endl;
  for (size_t i = 0; i < graphSize; ++i)
  {
    printRow(out, verts[i], std::vector< int >(values.begin() + i * graphSize, values.begin() + (i + 1) * graphSize));
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
void avdeeva::Graph::getUnion(Graph & lhs,
    const std::string & vlhs,
    Graph & rhs, const std::string & vrhs,
    int value)
{
  if (lhs.checkSimilarVerts(rhs))
  {
    throw std::invalid_argument("There are similar vertexes in graphs. Use command RENAME");
  }
  size_t lhsSize = lhs.verts.size();
  size_t rhsSize = rhs.verts.size();
  values.reserve((lhsSize + rhsSize) * (lhsSize + rhsSize));
  auto beginIt = lhs.values.begin();
  auto endIt = beginIt + lhsSize;
  for (size_t i = 0; i < lhsSize; ++i)
  {
    std::copy(beginIt, endIt, std::back_inserter(values));
    std::fill_n(std::back_inserter(values), rhsSize, 0);
    beginIt = endIt;
    endIt = endIt + lhsSize;
  }
  beginIt = rhs.values.begin();
  endIt = beginIt + rhsSize;
  for (size_t i = 0; i < rhsSize; ++i)
  {
    std::fill_n(std::back_inserter(values), lhsSize, 0);
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
