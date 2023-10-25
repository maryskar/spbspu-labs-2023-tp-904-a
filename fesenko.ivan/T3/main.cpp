#include <iostream>
#include <fstream>
#include <iterator>
#include <deque>
#include <limits>
#include <messages.h>
#include "commands.h"

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
  fesenko::Commands commands;
  std::string cmd = "";
  while (std::cin >> cmd) {
    try {
      commands.make(cmd, polygons, std::cin, std::cout);
    } catch (const std::exception &e) {
      std::cout << e.what() << "\n";
      return 2;
    }
  }
}
