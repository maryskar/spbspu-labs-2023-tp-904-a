#include "str-work.hpp"

std::vector< std::string > turkin::split_str(std::string & str, std::string del)
{
  std::vector< std::string > result;
  int end = str.find(del);
  while (end != -1)
  {
    result.push_back(str.substr(0, end));
    str.erase(str.begin(), str.begin() + end + 1);
    end = str.find(del);
  }
  result.push_back(str.substr(0, end));
  return result;
}
