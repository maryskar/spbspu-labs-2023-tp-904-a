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
      int nextChar = file.peek();

      if (nextChar != '\n' && nextChar != -1) {
        file.ignore(streamsize_limits::max(), '\n');
      }
    }
  }

  auto commands = kumachev::createCommandSystem();
  std::istream &in = std::cin;
  std::ostream &out = std::cout;

  while (!in.eof()) {
    try {
      auto command = kumachev::inputCommand(in);
      kumachev::handleCommand(command, commands, shapes, in, out);
      out << '\n';
    }
    catch (const std::logic_error &e) {
      kumachev::printInvalid(out);
      out << '\n';
      in.clear();
      int nextChar = in.peek();

      if (nextChar != '\n' && nextChar != -1) {
        in.ignore(streamsize_limits::max(), '\n');
      }
    }
    catch (const std::runtime_error &e) {
      break;
    }
  }

  return 0;
}
