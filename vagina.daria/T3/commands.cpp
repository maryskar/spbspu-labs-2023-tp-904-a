#include "commands.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <IOFmtGuard.h>

bool vagina::isEven(const Polygon& pol)
{
  return (pol.points.size() % 2 == 0);
}
bool vagina::isOdd(const Polygon& pol)
{
  return !isEven(pol);
}
bool vagina::isCountOfVertexes(const Polygon& pol, std::size_t param)
{
  return (pol.points.size() == param);
}
void vagina::areaEven(const std::vector< Polygon >& dest, std::ostream& out)
{
  std::vector< Polygon > tmp (dest.size());
  std::copy_if(dest.begin(), dest.end(), tmp.begin(), isEven);
  std::size_t count = std::count_if(dest.begin(), dest.end(), isEven);
  std::vector< double > tmpS(count);
  auto fin = tmp.begin() + count;
  std::transform(tmp.begin(), fin, std::back_inserter(tmpS), getArea);
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1) << std::accumulate(tmpS.begin(), tmpS.end(), 0.0) << "\n";
}
void vagina::areaOdd(const std::vector< Polygon >& dest, std::ostream& out)
{
  std::vector< Polygon > tmp (dest.size());
  std::copy_if(dest.begin(), dest.end(), tmp.begin(), isOdd);
  std::size_t count = std::count_if(dest.begin(), dest.end(), isOdd);
  std::vector< double > tmpS(count);
  auto fin = tmp.begin() + count;
  std::transform(tmp.begin(), fin, std::back_inserter(tmpS), getArea);
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1) << std::accumulate(tmpS.begin(), tmpS.end(), 0.0) << "\n";
}
void vagina::areaMean(const std::vector< Polygon >& dest, std::ostream& out)
{
  if (dest.empty())
  {
    throw std::invalid_argument("Invalid parameter");
  }
  std::vector< double > tmp(dest.size());
  std::transform(dest.begin(), dest.end(), tmp.begin(), getArea);
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1) << std::accumulate(tmp.begin(), tmp.end(), 0.0) / dest.size() << "\n";
}
void vagina::areaVertexes(const std::vector< Polygon >& dest, std::ostream& out, std::size_t param)
{
  if (param < 3)
  {
    throw std::invalid_argument("Invalid parameter");
  }
  using namespace std::placeholders;
  auto countVert = std::bind(isCountOfVertexes, _1, param);
  std::vector< Polygon > tmp (dest.size());
  std::copy_if(dest.begin(), dest.end(), tmp.begin(), countVert);
  std::size_t count = std::count_if(dest.begin(), dest.end(), countVert);
  std::vector< double > tmpS(count);
  auto fin = tmp.begin() + count;
  std::transform(tmp.begin(), fin, tmpS.begin(), getArea);
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1) << std::accumulate(tmpS.begin(), tmpS.end(), 0.0) << "\n";
}
void vagina::maxArea(const std::vector < Polygon >& dest, std::ostream& out)
{
  if (dest.empty())
  {
    throw std::invalid_argument("Invalid parameter");
  }
  std::vector< Polygon > tmp(dest.size());
  std::copy(dest.begin(), dest.end(), tmp.begin());
  std::sort(tmp.begin(), tmp.end(), comparatorArea);
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1) << getArea(tmp[0]) << "\n";
}
void vagina::maxVertexes(const std::vector < Polygon >& dest, std::ostream& out)
{
  if (dest.empty())
  {
    throw std::invalid_argument("Invalid parameter");
  }
  std::vector< Polygon > tmp(dest.size());
  std::copy(dest.begin(), dest.end(), tmp.begin());
  std::sort(tmp.begin(), tmp.end(), comparatorVertexes);
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1) << tmp[0].points.size() << "\n";
}
void vagina::minArea(const std::vector < Polygon >& dest, std::ostream& out)
{
  if (dest.empty())
  {
    throw std::invalid_argument("Invalid parameter");
  }
  std::vector< Polygon > tmp(dest.size());
  std::copy(dest.begin(), dest.end(), tmp.begin());
  std::sort(tmp.begin(), tmp.end(), comparatorArea);
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1) << getArea(tmp[tmp.size() - 1]) << "\n";
}
void vagina::minVertexes(const std::vector < Polygon >& dest, std::ostream& out)
{
  if (dest.empty())
  {
    throw std::invalid_argument("Invalid parameter");
  }
  std::vector< Polygon > tmp(dest.size());
  std::copy(dest.begin(), dest.end(), tmp.begin());
  std::sort(tmp.begin(), tmp.end(), comparatorVertexes);
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1) << tmp[0].points.size() << "\n";
}
void vagina::countEven(const std::vector < Polygon >& dest, std::ostream& out)
{
  iofmtguard iofmtguard(out);
  out << std::count_if(dest.begin(), dest.end(), isEven) << "\n";
}
void vagina::countOdd(const std::vector < Polygon >& dest, std::ostream& out)
{
  iofmtguard iofmtguard(out);
  out << std::count_if(dest.begin(), dest.end(), isOdd) << "\n";
}
void vagina::countVertexes(const std::vector < Polygon >& dest, std::ostream& out, std::size_t param)
{
  if (param < 3)
  {
    throw std::invalid_argument("Invalid parameter");
  }
  using namespace std::placeholders;
  auto countVert = std::bind(isCountOfVertexes, _1, param);
  iofmtguard iofmtguard(out);
  out << std::count_if(dest.begin(), dest.end(), countVert) << "\n";
}
void vagina::rects(const std::vector < Polygon >& dest, std::ostream& out)
{
  iofmtguard iofmtguard(out);
  out << std::count_if(dest.begin(), dest.end(), isRectangle) << "\n";
}
bool vagina::isPerm(const Polygon& lhs, const Polygon& rhs)
{
  return std::is_permutation(lhs.points.begin(), lhs.points.end(), rhs.points.begin(), rhs.points.end());
}
void vagina::perms(const std::vector < Polygon >& dest, std::ostream& out, std::istream& in)
{
  Polygon pol;
  in >> pol;
  if (pol.points.size() < 3)
  {
    throw std::invalid_argument("Invalid parameter");
  }
  using namespace std::placeholders;
  auto perm = std::bind(isPerm, _1, pol);
  iofmtguard iofmtguard(out);
  out << std::count_if(dest.begin(), dest.end(), perm) << '\n';
}
void vagina::messageInvalidCommand(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}
vagina::DictionaryOfCommands::DictionaryOfCommands()
{
  polygon.insert({"AREA EVEN", areaEven});
  polygon.insert({"AREA ODD", areaOdd});
  polygon.insert({"AREA MEAN", areaMean});
  polygon.insert({"MAX AREA", maxArea});
  polygon.insert({"MAX VERTEXES", maxVertexes});
  polygon.insert({"MIN AREA", minArea});
  polygon.insert({"MIN VERTEXES", minVertexes});
  polygon.insert({"COUNT EVEN", countEven});
  polygon.insert({"COUNT ODD", countOdd});
  polygon.insert({"RECTS", rects});
  vertexes.insert({"AREA NUM", areaVertexes});
  vertexes.insert({"COUNT NUM", countVertexes});
  permutation.insert({"PERMS", perms});
}
std::string vagina::readCommand(std::istream& in)
{
  std::string comm = " ";
  in >> comm;
  if (!in)
  {
    throw std::runtime_error("EOF");
  }
  if (comm != "PERMS" && comm != "RECTS")
  {
    std::string param = " ";
    in >> param;
    if (!in)
    {
      throw std::invalid_argument("Invalid parameter");
    }
    comm += " ";
    comm += param;
  }
  return comm;
}
void vagina::DictionaryOfCommands::doCommPerms(const std::string& command, const std::vector< Polygon >& data, std::ostream& out, std::istream& in) const
{
  auto func = permutation.at(command);
  func(data, out, in);
}
void vagina::DictionaryOfCommands::doCommVert(const std::string& command, const std::vector< Polygon >& data, std::ostream& out, size_t n) const
{
  auto func = vertexes.at(command);
  func(data, out, n);
}
void vagina::DictionaryOfCommands::doCommPoly(const std::string& command, const std::vector< Polygon >& data, std::ostream& out) const
{
  auto func = polygon.at(command);
  func(data, out);
}
void vagina::doCommand(const std::string& command, const DictionaryOfCommands& commands,
  const std::vector< Polygon >& dest, std::istream& in, std::ostream& out)
{
  try
  {
    commands.doCommPerms(command, dest, out, in);
    return;
  }
  catch (const std::out_of_range & e)
  {}
  try
  {
    commands.doCommPoly(command, dest, out);
    return;
  }
  catch (const std::out_of_range & e)
  {}
  std::size_t space = command.find(' ');
  std::size_t num = std::stoull(command.substr(space));
  commands.doCommVert((command.substr(0, space) + " NUM"), dest, out, num);
}
