#include "commands.h"
#include <iomanip>
#include "extra_commands.h"

namespace mishanina{
//Расчёт суммы площади фигур с чётным количеством вершин
  void printAreaEven(const std::vector<Polygon>& polygons, std::ostream& out){
//    mishanina::iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << mishanina::getAreaIf(polygons, isEven) << '\n';
  }
//Расчёт суммы площади фигур с нечётным количеством вершин
  void printAreaOdd(const std::vector<Polygon>& polygons, std::ostream& out){
    out << std::fixed << std::setprecision(1) << mishanina::getAreaIf(polygons, isOdd) << '\n';
  }
//Расчёт среднего площадей фигур
  void printAreaMean(const std::vector<Polygon>& polygons, std::ostream& out){
    if (polygons.empty()) {
      throw std::invalid_argument("ERROR : polygons are empty");
    }
    std::vector<double> areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), areas.begin(), mishanina::getArea);

    double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
    double mean = sum / polygons.size();
//    mishanina::iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << mean << '\n';
  }
}