#include "read-and-do-command.hpp"
#include <iostream>
#include <functional>

std::string chemodurov::readCommand(std::istream & in)
{
  std::string res;
  in >> res;
  if (!in)
  {
    throw std::invalid_argument("Invalid command");
  }
  if (res == "RECTS")
  {
    return res;
  }
  std::string temp;
  in >> temp;
  if (!in)
  {
    throw std::invalid_argument("Invalid command");
  }
  res += ' ';
  res += temp;
  return res;
}

void chemodurov::doCommand(const std::string & name_comm,
    const chemodurov::comm_dics_t & commands,
    const std::vector< Polygon > & data,
    std::istream & in,
    std::ostream & out)
{
  using namespace std::placeholders;
  try
  {
    auto func = std::bind(commands.dic3.at(name_comm), _1, std::ref(out), std::ref(in));
    func(data);
    return;
  }
  catch (const std::out_of_range & e)
  {}
  try
  {
    auto func = std::bind(commands.dic1.at(name_comm), _1, std::ref(out));
    func(data);
    return;
  }
  catch (const std::out_of_range & e)
  {}
  size_t space = name_comm.find(' ');
  size_t num = std::stoull(name_comm.substr(space));
  auto func = std::bind(commands.dic2.at(name_comm.substr(0, space) + " NUM"), _1, std::ref(out), num);
  func(data);
}
