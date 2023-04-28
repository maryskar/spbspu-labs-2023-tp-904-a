#ifndef ROMANOVICH_ARTEM_INPUT_H
#define ROMANOVICH_ARTEM_INPUT_H
#include <tuple>
#include <string>
using constr = const std::string;
using return_tuple = std::tuple< unsigned long long, std::pair< long long, unsigned long long >, std::string >;
using string_pair = std::tuple< std::string, std::string >;
return_tuple parseLine(constr &str, constr &divEl, constr &divKV, std::string list[3]);
string_pair getKeyValue(constr &kv, constr &divKV);
return_tuple fillTuple(constr *list, constr &key, constr &value, return_tuple &tuple);
std::string tryRemoveBrackets(constr &str);
#endif
