#include <string>
#include <iostream>
#include <tuple>
using return_tuple = std::tuple<unsigned long long, std::pair<long long, unsigned long long>>;
using string_pair = std::tuple<std::string, std::string>;
string_pair getKeyValue(const std::string &str, int begin, int end, const std::string &divider2)
{
  const std::string &kv = str.substr(begin, end - begin);
  const std::string &new_kv = kv;
  std::string key = kv.substr(0, static_cast<int>(str.find(divider2)));
  std::string value = new_kv.substr(static_cast<int>(str.find(divider2)) + 1, new_kv.size() - 1);
  return {key, value};
}
return_tuple parseLine(const std::string &str, const std::string &divider, const std::string &divider2)
{
  int intBegin = 0;
  int intEnd = static_cast<int>(str.find(divider));
  while (intEnd != -1)
  {
    std::string key = std::get<0>(getKeyValue(str, intBegin, intEnd, divider2));
    std::string value = std::get<1>(getKeyValue(str, intBegin, intEnd, divider2));
    std::cout << key << std::endl;
    std::cout << value << std::endl;
    intBegin = intEnd + 1;
    intEnd = static_cast<int>(str.find(divider, intBegin));
  }
  std::string key = std::get<0>(getKeyValue(str, intBegin, intEnd, divider2));
  std::string value = std::get<1>(getKeyValue(str, intBegin, intEnd, divider2));
  std::cout << key << std::endl;
  std::cout << value << std::endl;
  return {0, std::make_pair(0, 0)};
}
int main()
{
  for (std::string line; std::getline(std::cin, line);)
  {
    if (line.size() < 4)
    {
      continue;
    }
    line = line.substr(2, line.size() - 4);
    auto a = parseLine(line, ":", " ");
  }
  return 0;
}
