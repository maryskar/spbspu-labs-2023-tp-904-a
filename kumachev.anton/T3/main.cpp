#include <fstream>
#include <vector>
#include <limits>
#include <iterator>
#include <iostream>
#include "polygon.h"
#include "polygon_io.h"
#include "command_system.h"

int main(int argc, char **argv)
{
  using streamsize_limits = std::numeric_limits< std::streamsize >;
  using istream_iterator = std::istream_iterator< kumachev::Polygon >;

  if (argc != 2) {
    return 1;
  }

  std::ifstream file(argv[1]);

  if (!file.is_open()) {
    return 1;
  }

  std::vector< kumachev::Polygon > shapes;
  auto backInserter = std::back_inserter(shapes);

  while (!file.eof()) {
    std::copy(istream_iterator(file), istream_iterator(), backInserter);

    if (file.fail()) {
      file.clear();
      file.ignore(streamsize_limits::max(), '\n');
    }
  }

  std::istream &in = std::cin;
  std::ostream &out = std::cout;
  kumachev::CommandSystem commandSystem(in, out, shapes);

  while (!in.eof()) {
    try {
      auto command = commandSystem.inputCommand();
      commandSystem.handleCommand(command);
      out << '\n';
    }
    catch (const std::logic_error &e) {
      kumachev::printInvalid(out);
      out << '\n';
      in.clear();
      in.ignore(streamsize_limits::max(), '\n');
    }
    catch (const std::runtime_error &e) {
      break;
    }
  }

  return 0;
}
