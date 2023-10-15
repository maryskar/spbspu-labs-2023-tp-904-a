#include "commands.h"
#include <messages.h>
#include "subCommands.h"

fesenko::Commands::Commands():
  type1(),
  type2()
{
  type1.insert(std::make_pair("AREA", &area_vertexes));
  type1.insert(std::make_pair("COUNT", &count_vertexes));
  type1.insert(std::make_pair("INFRAME", &inframe));

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
}

void fesenko::Commands::make(const std::string &command1, data_t &data, std::istream &in, std::ostream &out)
{
  try {
    char c1 = ' ';
    in.get(c1);
    if (c1 != ' ') {
      type2.at(command1)(data, out) << "\n";
      return;
    } else {
      char c2;
      in.get(c2);
      in.putback(c2);
      if (std::isdigit(c2)) {
        type1.at(command1)(data, in, out) << "\n";
        return;
      }
    }
    std::string command2 = "";
    in >> command2;
    type2.at(command1 + " " + command2)(data, out) << "\n";
  } catch (...) {
    outInvalidCommandMessage(out);
    out << "\n";
    in.clear();
    std::string trash = "";
    getline(in, trash);
  }
}
