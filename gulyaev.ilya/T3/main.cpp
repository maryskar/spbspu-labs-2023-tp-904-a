#include <fstream>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <vector>
#include <limits>
#include "do-commands.hpp"
#include "polygon.hpp"

int main(int argc, char **argv)
{
  using namespace gulyaev;
  if (argc != 2) {
    std::cerr << "Command line parameters are incorrect\n";
    return 1;
  }
  std::ifstream input_file(argv[1]);
  if (!input_file.is_open()) {
    std::cerr << "Failed to open file\n";
    return 1;
  }
  std::vector< Polygon > data;
  while (!input_file.eof()) {
    std::copy(std::istream_iterator< Polygon >(input_file),
        std::istream_iterator< Polygon >(),
        std::back_inserter(data)
    );
    if (input_file.fail()) {
      input_file.clear();
      input_file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  doCommands(std::cin, std::cout, data);
  return 0;
}
