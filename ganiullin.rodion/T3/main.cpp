#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>

#include "Commands.h"
#include "Geometry.h"
#include "TypesIO.h"

constexpr size_t MAX_STREAM_SIZE = std::numeric_limits< std::streamsize >::max();

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Not enough arguments" << '\n';
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "Couldn't open a file" << '\n';
    return 1;
  }
  std::vector< ganiullin::Polygon > polygons;
  while (!file.eof()) {
    using inputPolyIt = std::istream_iterator< ganiullin::Polygon >;
    std::copy(inputPolyIt(file), inputPolyIt(), std::back_inserter(polygons));
    if (!file) {
      file.clear();
      file.ignore(MAX_STREAM_SIZE, '\n');
    }
  }
  file.close();

  ganiullin::CommandHandler commandHandler{};

  while (!std::cin.eof()) {
    try {
      std::string command = commandHandler.readCommand(std::cin);
      commandHandler.execCommand(command, polygons, std::cin, std::cout);
    } catch (const std::logic_error& e) {
      std::cin.setstate(std::ios::failbit);
    } catch (const std::runtime_error& e) {
      break;
    }
    if (!std::cin) {
      ganiullin::printErrorMessage(std::cout);
      std::cin.clear();
      std::cin.ignore(MAX_STREAM_SIZE, '\n');
    }
    std::cout << '\n';
  }
  return 0;
}
