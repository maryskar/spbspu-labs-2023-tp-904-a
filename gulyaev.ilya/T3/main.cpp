#include <fstream>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <vector>
#include <limits>
#include <map>
#include <functional>
#include "commands.hpp"
#include "polygon.hpp"
#include "iofmtguard.hpp"

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
    if (input_file.fail()) {
      input_file.clear();
      input_file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(std::istream_iterator< Polygon >(input_file),
        std::istream_iterator< Polygon >(),
        std::back_inserter(data)
    );
  }
  using cmd_t = std::function< void (const std::vector< Polygon > &, std::istream &, std::ostream &) >;
  std::map< std::string, cmd_t > cmds {
      {"AREA", printArea},
      {"MAX", printMax},
      {"MIN", printMin},
      {"COUNT", printCount},
      {"PERMS", printPerms},
      {"RIGHTSHAPES", printRightShapes}
  };
  while (!std::cin.eof()) {
    std::string cmd;
    std::cin >> cmd;
    if (std::cin.eof()) {
      continue;
    }
    try {
      auto toexecute = cmds.at(cmd);
      iofmtguard ofmtguard(std::cout);
      iofmtguard ifmtguard(std::cin);
      std::cin.unsetf(std::ios::skipws);
      toexecute(data, std::cin, std::cout);
    } catch (const std::out_of_range &e) {
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cerr << "INVALID COMMAND\n";
    } catch (const std::invalid_argument &e) {
      std::cerr << e.what() << "\n";
    } catch (const std::bad_alloc &e) {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  return 0;
}
