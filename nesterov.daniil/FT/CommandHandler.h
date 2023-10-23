#ifndef FT_COMMANDHANDLER_H
#define FT_COMMANDHANDLER_H

#include <functional>
#include <deque>
#include "Graph.h"

namespace nesterov
{
  using graphsMap = std::unordered_map< std::string, std::shared_ptr< Graph > >;

  using base_cmd_t = std::function<
    void (std::ostream &)
  >;

  using const_cmd_t = std::function<
    void (const graphsMap &,
      std::istream &,
      std::ostream &,
      std::ostream &
    )
  >;

  using cmd_t = std::function<
    void (graphsMap &,
      std::istream &,
      std::ostream &,
      std::ostream &
    )
  >;

  void executeExistsVertexCommand(const graphsMap &map, std::istream &in, std::ostream &out, std::ostream &err);
  void executeExistsArcCommand(const graphsMap &map, std::istream &in, std::ostream &out, std::ostream &err);
  void executeDfsCommand(const graphsMap &map, std::istream &in, std::ostream &out, std::ostream &err);
  void executeSortCommand(const graphsMap &map, std::istream &in, std::ostream &out, std::ostream &err);
  void executeCreateCommand(graphsMap &map, std::istream &in, std::ostream &out, std::ostream &err);
  void executeDeleteCommand(graphsMap &map, std::istream &in, std::ostream &out, std::ostream &err);
  void executeAddVertexCommand(graphsMap &map, std::istream &in, std::ostream &out, std::ostream &err);
  void executeRemoveVertexCommand(graphsMap &map, std::istream &in, std::ostream &out, std::ostream &err);
  void executeAddArcCommand(graphsMap &map, std::istream &in, std::ostream &out, std::ostream &err);
  void executeRemoveArcCommand(graphsMap &map, std::istream &in, std::ostream &out, std::ostream &err);
  void executeHelpCommand(std::ostream &out);
}

#endif
