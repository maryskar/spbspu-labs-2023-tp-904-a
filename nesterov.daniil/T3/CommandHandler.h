#ifndef T3_NEW_COMMANDHANDLER_H
#define T3_NEW_COMMANDHANDLER_H

#include <functional>
#include <deque>
#include "Polygon.h"

namespace nesterov
{
  using const_cmd_t = std::function<
    void (const std::deque< Polygon > &,
         std::istream &,
         std::ostream &
    )
  >;
  using cmd_t = std::function<
    void (std::deque< Polygon > &,
         std::istream &,
         std::ostream &
    )
  >;

  void executeAreaCommand(const std::deque< Polygon > &pls, std::istream &in, std::ostream &out);
  void executeMaxCommand(const std::deque< Polygon > &pls, std::istream &in, std::ostream &out);
  void executeMinCommand(const std::deque< Polygon > &pls, std::istream &in, std::ostream &out);
  void executeCountCommand(const std::deque< Polygon > &pls, std::istream &in, std::ostream &out);
  void executeMaxSeqCommand(const std::deque< Polygon > &pls, std::istream &in, std::ostream &out);
  void executeEchoCommand(std::deque< Polygon > &pls, std::istream &in, std::ostream &out);
}

#endif
