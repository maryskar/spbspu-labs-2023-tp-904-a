#include <ostream>
#include <iostream>
#include <fstream>
#include "functions.h"
#include "dictionary.h"
#include "read_and_do_comm.h"

std::ostream & outInvalidCommand(std::ostream & out)
{
  out << "<INVALID COMMAND>";
  return out;
}
std::string getCommand(std::istream & in)
{
  std::string res;
  in >> res;
  if (!in)
  {
    throw std::runtime_error("eof");
  }
  return res;
}

int main()
{
  kryuchkova::CommandDict commDict;
  std::map< std::string, kryuchkova::ErDictionary > dicts;
  while (!std::cin.eof())
  {
    try
    {
      auto comm = getCommand(std::cin);
      commDict.handleCommand(comm, std::cin, std::cout, dicts);
    }
    catch (const std::logic_error & e)
    {
      outInvalidCommand(std::cout) << '\n';
      std::cout << e.what();
    }
    catch (const std::runtime_error & e)
    {
      break;
    }
  }
  return 0;
}
