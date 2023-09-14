#include <iostream>
#include <fstream>
#include <iterator>
#include <deque>
#include <limits>
#include <messages.h>
#include "commandsList.h"

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cerr << "Invalid number of arguments\n";
    return 2;
  }
  std::ifstream in(argv[1]);
  if (!in) {
    std::cerr << "Can`t open the file\n";
    return 2;
  }
  std::deque< fesenko::Polygon > polygons;
  while (!in.eof()) {
    std::copy(std::istream_iterator< fesenko::Polygon >(in),
      std::istream_iterator< fesenko::Polygon >(),
      std::back_inserter(polygons)
    );
    if (in.fail()) {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  while (!std::cin.eof()) {
    std::string cmd;
    std::cin >> cmd;
    if (!std::cin) {
      break;
    }
    try {
      fesenko::main_list.at(cmd)(polygons, std::cin, std::cout) << "\n";
    } catch (...) {
      fesenko::outInvalidCommandMessage(std::cout);
      std::cout << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
