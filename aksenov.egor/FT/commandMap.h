#ifndef COMMANDMAP_H
#define COMMANDMAP_H
#include <map>
#include <string>
#include <iostream>
#include <functional>
#include "commands.h"
using namespace std::placeholders;
using command_t = std::function< void(const std::string&) >;
std::map< std::string, command_t > createFunctionMap(dict_t &dicts, std::ostream &out);
#endif
