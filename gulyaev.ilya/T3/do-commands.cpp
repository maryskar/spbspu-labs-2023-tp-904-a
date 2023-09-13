#include <map>
#include <functional>
#include <limits>
#include "commands.hpp"
#include "iofmtguard.hpp"

namespace gulyaev
{
  using cmd_t = std::function< void (const std::vector< Polygon > &, std::istream &, std::ostream &) >;
  std::map< std::string, cmd_t > cmds {
      {"AREA", printArea},
      {"MAX", printMax},
      {"MIN", printMin},
      {"COUNT", printCount},
      {"PERMS", printPerms},
      {"RIGHTSHAPES", printRightShapes}
  };
  void doCommands(std::istream &in, std::ostream &out, std::vector< Polygon > data)
  {
    while (!in.eof()) {
      std::string cmd;
      in >> cmd;
      if (in.eof()) {
        continue;
      }
      try {
        if (data.empty()) {
          out << "<INVALID COMMAND>" << "\n";
        } else {
          auto toexecute = cmds.at(cmd);
          iofmtguard ofmtguard(out);
          toexecute(data, in, out);
        }
      } catch (const std::out_of_range &e) {
        in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        out << "<INVALID COMMAND>\n";
      } catch (const std::invalid_argument &e) {
        out << e.what() << "\n";
      } catch (const std::bad_alloc &e) {
        out << e.what() << "\n";
        return;
      }
    }
  }
}
