// Пример перегрузки ввода/вывода для пользовательского типа DataStruct.
// Похожим образом можно организовать ввод/вывод в работе 1,
// но в этом примере имеется ряд упрощений:
// 1) не поддерживается произвольный порядок полей
// 2) не поддерживаются строки некорректного формата

#include <iostream>
#include <iterator>
#include <vector>

#include "Data.h"

int main() {
  std::vector<DataStruct> data;
  std::istringstream iss(
      "(:key1 2.5e-01:key2 0xA2:key3 \"Sanity is a prison\":)"
      "(:key4 \"Let madness release you\":key1 2.5e-01:key2 0xA2:)"
      "(:key3 \"Let madness release you\":key1 2.5e-01:key2 0xA2:)");

  std::copy(std::istream_iterator<DataStruct>(iss),
            std::istream_iterator<DataStruct>(), std::back_inserter(data));

  std::cout << "DataStruct:\n";
  std::copy(std::begin(data), std::end(data),
            std::ostream_iterator<DataStruct>(std::cout, "\n"));

  return 0;
}
