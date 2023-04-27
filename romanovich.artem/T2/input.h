#ifndef ROMANOVICH_ARTEM_INPUT_H
#define ROMANOVICH_ARTEM_INPUT_H
#include <tuple>
#include <string>
using return_tuple = std::tuple<unsigned long long, std::pair<long long, unsigned long long>, std::string>;
using string_pair = std::tuple<std::string, std::string>;
return_tuple parseLine(const std::string &str, const std::string &divEl, const std::string &divKV, std::string list[3]);
string_pair getKeyValue(const std::string &kv, const std::string &divKV);
return_tuple fillTuple(const std::string *list, const std::string &key, const std::string &value, return_tuple &tuple);
std::string tryRemoveBrackets(const std::string& str);
#endif
