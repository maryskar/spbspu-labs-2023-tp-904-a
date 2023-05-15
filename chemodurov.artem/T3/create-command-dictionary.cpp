#include "create-command-dictionary.hpp"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <functional>
#include <cmath>
#include <iofmtguard.hpp>
#include <iomanip>
#include "is-nearly-equal.hpp"

namespace chemodurov
{
  bool isOdd(const Polygon & pol)
  {
    return (size(pol) % 2 == 1);
  }

  bool isEven(const Polygon & pol)
  {
    return !isOdd(pol);
  }

  double transIntoOddArea(const Polygon & pol)
  {
    return isOdd(pol) ? calcArea(pol) : 0.0;
  }

  double transIntoEvenArea(const Polygon & pol)
  {
    return isEven(pol) ? calcArea(pol) : 0.0;
  }

  template< typename P >
  void printAreaIf(const std::vector< Polygon > & data, std::ostream & out, P p)
  {
    std::vector< double > areas;
    std::transform(data.begin(), data.end(), std::back_inserter(areas), p);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(areas.begin(), areas.end(), 0.0) << '\n';
  }

  void printAreaOdd(const std::vector< Polygon > & data, std::ostream & out)
  {
    printAreaIf(data, out, transIntoOddArea);
  }

  void printAreaEven(const std::vector< Polygon > & data, std::ostream & out)
  {
    printAreaIf(data, out, transIntoEvenArea);
  }

  void printAreaMean(const std::vector< Polygon > & data, std::ostream & out)
  {
    if (data.empty())
    {
      throw std::invalid_argument("For mean area must be at least one polygon");
    }
    std::vector< double > areas;
    std::transform(data.begin(), data.end(), std::back_inserter(areas), calcArea);
    double sum_area = std::accumulate(areas.begin(), areas.end(), 0.0);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << (sum_area / data.size()) << '\n';
  }

  bool isNumOfVerts(const Polygon & pol, size_t num)
  {
    return size(pol) == num;
  }

  double transIntoAreaNumOfVerts(const Polygon & pol, size_t num)
  {
    return (isNumOfVerts(pol, num)) ? calcArea(pol) : 0.0;
  }

  void printAreaNumOfVerts(const std::vector< Polygon > & data, std::ostream & out, size_t num)
  {
    using namespace std::placeholders;
    auto trans = std::bind(transIntoAreaNumOfVerts, _1, num);
    printAreaIf(data, out, trans);
  }

  bool isLessArea(const Polygon & lhs, const Polygon & rhs)
  {
    return calcArea(lhs) < calcArea(rhs);
  }

  template< typename P1, typename P2 >
  void printMinOrMax(const std::vector< Polygon > & data, std::ostream & out, P1 p1, P2 p2)
  {
    auto it = std::max_element(data.begin(), data.end(), p1);
    if (it == data.end())
    {
      throw std::invalid_argument("For max area/vertexes must be at least one polygon");
    }
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << p2(*it) << '\n';
  }

  template< typename P >
  void printMaxOrMinArea(const std::vector< Polygon > & data, std::ostream & out, P p)
  {
    printMinOrMax(data, out, p, calcArea);
  }

  void printMaxArea(const std::vector< Polygon > & data, std::ostream & out)
  {
    printMaxOrMinArea(data, out, isLessArea);
  }

  void printMinArea(const std::vector< Polygon > & data, std::ostream & out)
  {
    using namespace std::placeholders;
    printMaxOrMinArea(data, out, std::bind(isLessArea, _2, _1));
  }

  bool isLessVerts(const Polygon & lhs, const Polygon & rhs)
  {
    return size(lhs) < size(rhs);
  }

  template< typename P >
  void printMaxOrMinVerts(const std::vector< Polygon > & data, std::ostream & out, P p)
  {
    printMinOrMax(data, out, p, size);
  }

  void printMaxVerts(const std::vector< Polygon > & data, std::ostream & out)
  {
    printMaxOrMinVerts(data, out, isLessVerts);
  }

  void printMinVerts(const std::vector< Polygon > & data, std::ostream & out)
  {
    using namespace std::placeholders;
    printMaxOrMinVerts(data, out, std::bind(isLessVerts, _2, _1));
  }

  template< typename P >
  void countIf(const std::vector< Polygon > & data, std::ostream & out, P p)
  {
    if (data.empty())
    {
      throw std::invalid_argument("No polygon to count");
    }
    out << std::count_if(data.begin(), data.end(), p) << '\n';
  }

  void countOdd(const std::vector< Polygon > & data, std::ostream & out)
  {
    countIf(data, out, isOdd);
  }

  void countEven(const std::vector< Polygon > & data, std::ostream & out)
  {
    countIf(data, out, isEven);
  }

  void countIfNumOfVerts(const std::vector< Polygon > & data, std::ostream & out, size_t num)
  {
    using namespace std::placeholders;
    auto pred = std::bind(isNumOfVerts, _1, num);
    countIf(data, out, pred);
  }

  void printMaxSeq(const std::vector< Polygon > & data, std::ostream & out, std::istream & in)
  {
    Polygon temp;
    in >> temp;
    if (!in)
    {
      throw std::invalid_argument("Invalid MAXSEQ");
    }
    size_t max_seq = 0;
    using namespace std::placeholders;
    auto pred = std::bind(std::equal_to< Polygon >{}, _1, temp);
    auto beg_ = data.begin();
    while (beg_ != data.end())
    {
      beg_ = std::find_if(beg_, data.end(), pred);
      auto end_ = std::find_if_not(beg_, data.end(), pred);
      max_seq = std::max(max_seq, static_cast< size_t >(std::abs(std::distance(beg_, end_))));
      beg_ = end_;
    }
    out << max_seq << '\n';
  }

  double calcLength(const Point & lhs, const Point & rhs)
  {
    double dx = rhs.x - lhs.x;
    double dy = rhs.y - lhs.y;
    return std::sqrt(dx * dx + dy * dy);
  }

  bool isRectangle(const Polygon & pol)
  {
    if (size(pol) != 4ull)
    {
      return false;
    }
    bool is_equal_sides1 = isNearlyEqual(calcLength(pol.data[0], pol.data[1]), calcLength(pol.data[2], pol.data[3]));
    bool is_equal_sides2 = isNearlyEqual(calcLength(pol.data[1], pol.data[2]), calcLength(pol.data[0], pol.data[3]));
    bool is_equal_diagonals = isNearlyEqual(calcLength(pol.data[0], pol.data[2]), calcLength(pol.data[1], pol.data[3]));
    return is_equal_sides1 && is_equal_sides2 && is_equal_diagonals;
  }

  void printNumOfRects(const std::vector< Polygon > & data, std::ostream & out)
  {
    out << std::count_if(data.begin(), data.end(), isRectangle) << '\n';
  }

  comm_dics_t createCommandDictionary()
  {
    comm_dics_t res{};
    res.dic1.insert({"AREA ODD", printAreaOdd});
    res.dic1.insert({"AREA EVEN", printAreaEven});
    res.dic1.insert({"AREA MEAN", printAreaMean});
    res.dic1.insert({"MIN AREA", printMinArea});
    res.dic1.insert({"MAX AREA", printMaxArea});
    res.dic1.insert({"MIN VERTEXES", printMinVerts});
    res.dic1.insert({"MAX VERTEXES", printMaxVerts});
    res.dic1.insert({"COUNT EVEN", countEven});
    res.dic1.insert({"COUNT ODD", countOdd});
    res.dic1.insert({"RECTS", printNumOfRects});
    res.dic2.insert({"AREA NUM", printAreaNumOfVerts});
    res.dic2.insert({"COUNT NUM", countIfNumOfVerts});
    res.dic3.insert({"MAXSEQ", printMaxSeq});
    return res;
  }
}
