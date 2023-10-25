#ifndef CONVERTTOPOSTFIXNOTATION_H
#define CONVERTTOPOSTFIXNOTATION_H
#include <fstream>
#include <string>
#include <queue>
#include <stack>

namespace mashkin
{
  void convertToPostNot(const std::string& line, std::queue< std::string >& que);
}
#endif
