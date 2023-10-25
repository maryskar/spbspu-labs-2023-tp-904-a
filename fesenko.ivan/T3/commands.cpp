#include "commands.h"
#include <string>
#include <messages.h>
#include <limits>
#include "subCommands.h"

fesenko::Commands::Commands():
  type1(),
  type2(),
  type3()
{
  type1.insert(std::make_pair("AREA", &area_vertexes));
  type1.insert(std::make_pair("COUNT", &count_vertexes));

  type2.insert(std::make_pair("AREA ODD", &area_odd));
  type2.insert(std::make_pair("AREA EVEN", &area_even));
  type2.insert(std::make_pair("AREA MEAN", &area_mean));
  type2.insert(std::make_pair("MAX AREA", &max_area));
  type2.insert(std::make_pair("MAX VERTEXES", &max_vertexes));
  type2.insert(std::make_pair("MIN AREA", &min_area));
  type2.insert(std::make_pair("MIN VERTEXES", &min_vertexes));
  type2.insert(std::make_pair("COUNT ODD", &count_odd));
  type2.insert(std::make_pair("COUNT EVEN", &count_even));
  type2.insert(std::make_pair("RECTS", &rects));

  type3.insert(std::make_pair("INFRAME", &inframe));
}

void fesenko::Commands::make(const std::string &command1, data_t &data, std::istream &in, std::ostream &out)
{
  try {
    if (type3.find(command1) != type3.end()) {
      type3.at(command1)(data, in, out) << "\n";
      return;
    } else if (type2.find(command1) != type2.end()) {
      type2.at(command1)(data, out) << "\n";
      return;
    }
    std::string command2 = "";
    in >> command2;
    if (std::isdigit(command2[0])) {
      type1.at(command1)(data, std::stoull(command2), out) << "\n";
    } else {
      type2.at(command1 + " " + command2)(data, out) << "\n";
    }
  } catch (...) {
    outInvalidCommandMessage(out);
    out << "\n";
    auto max_size = std::numeric_limits< std::streamsize >::max();
    in.ignore(max_size, '\n');
    in.clear();
  }
}
