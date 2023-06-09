#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <iterator>
#include "polygon.h"
#include "command_dict.h"
std::ostream &outInvalidCommandMessage(std::ostream &out)
{
  out << "<INVALID COMMAND>";
  return out;
}
std::string inputCommand(std::istream &in)
{
  std::string res;
  in >> res;
  if (!in)
  {
    throw std::runtime_error("Nothing to input");
  }
  if (res == "INTERSECTIONS" || res == "SAME")
  {
    return res;
  }
  std::string temp;
  in >> temp;
  if (!in)
  {
    throw std::invalid_argument("Invalid command");
  }
  res += ' ' + temp;
  return res;
}
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Check arguments\n";
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "File not open\n";
    return 2;
  }
  constexpr auto max_size = std::numeric_limits< std::streamsize >::max();
  using input_iter = std::istream_iterator< dimkashelk::Polygon >;
  std::vector< dimkashelk::Polygon > data;
  while (!in.eof())
  {
    std::copy(input_iter(in), input_iter(), std::back_inserter(data));
    if (!in)
    {
      in.clear();
      in.ignore(max_size, '\n');
    }
  }
  dimkashelk::CommandContainer commandContainer;
  while (!std::cin.eof())
  {
    try
    {
      auto command = inputCommand(std::cin);
      commandContainer.doCommand(command, data, std::cout, std::cin);
      std::cout << '\n';
    }
    catch (const std::logic_error &e)
    {
      outInvalidCommandMessage(std::cout) << '\n';
      std::cin.clear();
      std::cin.ignore(max_size, '\n');
    }
    catch (const std::runtime_error &e)
    {
      break;
    }
  }
  return 0;
}
