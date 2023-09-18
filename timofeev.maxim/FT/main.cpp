#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Commands.h"
#include "HelpFunction.h"

int main()
{
  std::setlocale(LC_ALL, "Russian");
  using Dictionary = std::map< std::string, std::vector< std::string > >;
  std::map<std::string, Dictionary> dictOfDict;
  std::map< std::string, void(*)(std::istream&, std::ostream&, std::map<std::string, Dictionary>& ) > commands;
  timofeev::command(commands);
  while (!std::cin.eof())
  {
    try
    {
      std::string firstPart;
      std::cin >> firstPart;
      if (commands.count(firstPart) > 0)
      {
        commands[firstPart](std::cin, std::cout, dictOfDict);
      }
      else
      {
        throw std::logic_error("Error");
      }
    }
    catch (const std::logic_error &e)
    {
      std::cout << "<INVALID COMMAND>" << "\n";
    }
    catch (const std::out_of_range &e)
    {
      timofeev::printEmpty(std::cout);
      return 1;
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
