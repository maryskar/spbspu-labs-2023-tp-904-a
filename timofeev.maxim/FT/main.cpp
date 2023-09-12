#include <iostream>
#include <fstream>
#include <limits>
#include <iterator>
#include <vector>
#include <map>
#include "Commands.h"
int main()
{
  setlocale(LC_ALL, "Russian");
  using Dictionary = std::map< std::string, std::vector<std::string> >;
  Dictionary engDict;
  Dictionary rusDict;

  std::map<std::string, Dictionary> dictOfDict;
  std::string Ru = "";
  std::string Eng = "";
  dictOfDict["Ru"] = rusDict;
  dictOfDict["Eng"] = engDict;
  std::map< std::string, void(*)(std::istream&, std::ostream&, std::map<std::string, Dictionary>& ) > commands;
  std::string firstPart;
  timofeev::command(commands);
  while (!std::cin.eof())
  {
    try
    {
      std::cin >> firstPart;

      commands[firstPart](std::cin, std::cout, dictOfDict);
    }
    catch (std::logic_error &e)
    {
      //printError(std::cout);
    }
    catch (const std::runtime_error & e)
    {
      break;
    }
  }
  if (std::cin.fail())
  {
    std::cin.clear();
  }
  return 0;
}
