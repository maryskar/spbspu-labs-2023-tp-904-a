#ifndef FT_COMMANDS_HPP
#define FT_COMMANDS_HPP
#include <algorithm>
#include <fstream>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "dictionary.hpp"

void createSet(Dictionary& dict, std::istream& in);
void threeMostPopular(const Dictionary& dict, std::ostream& out);
void print(const Dictionary& dict, std::ostream& out);


#endif