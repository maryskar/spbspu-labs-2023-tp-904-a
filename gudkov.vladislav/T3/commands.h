#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include "typesIO.h"
#include "scopeGuard.h"
#include "polygon.h"
#include "functions.h"

namespace gudkov
{
  std::string readCommand();
  void checkCommand(const std::string &command);

  std::string readSubcommand();
  std::string readSubcommand(const std::string &command);
  void checkSumcommand(const std::string &command, const std::string &subcommand);
  void checkForNumber(const std::string &str);

  void doArea(const std::vector< Polygon > &data, const std::string &subcommand);
  void max(const std::vector< Polygon > &data, const std::string &subcommand);
  void min(const std::vector< Polygon > &data, const std::string &subcommand);
  void count(const std::vector< Polygon > &data, const std::string &subcommand);
  void perms(const std::vector< Polygon > &data);
  void lessarea(const std::vector< Polygon > &data);
  void doCommand(const std::vector< Polygon > &data, const std::string &command, const std::string &subcommand);

  void error();
}
#endif
