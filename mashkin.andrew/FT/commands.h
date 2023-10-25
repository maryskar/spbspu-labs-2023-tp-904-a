#ifndef MASHKIN_ANDREW_COMMANDS_H
#define MASHKIN_ANDREW_COMMANDS_H
#include <iostream>
#include <map>
#include <string>
#include "semanticTree.h"

namespace mashkin
{
  void addExpr(std::istream& inp, std::map< std::string, std::shared_ptr< SemanticTree< std::string > > >& map);
  void simplifyExpr(std::istream& inp, std::map< std::string, std::shared_ptr< SemanticTree< std::string > > >& map);
  void getParameters(std::istream& inp, std::map< std::string, std::shared_ptr< SemanticTree< std::string > > >& map);
  void setNewExpr(std::istream& inp, std::map< std::string, std::shared_ptr< SemanticTree< std::string > > >& map);
  void showExpr(std::istream& inp, std::map< std::string, std::shared_ptr< SemanticTree< std::string > > >& map);
}
#endif
