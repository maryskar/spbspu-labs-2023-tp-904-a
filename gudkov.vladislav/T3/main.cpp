#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <exception>
#include "commands.h"
#include "polygon.h"

int main(int argc, char *argv[])
{
  using gudkov::Polygon;

  if (argc < 2)
  {
    std::cerr << "Error: filename is missing.\n";
    std::cerr << "Format: ./programName filename\n";
    return 1;
  }

  if (argc > 3)
  {
    std::cerr << "Error: incorrect format of command lines arguements.\n";
    std::cerr << "Format: ./programName filename\n";
    return 2;
  }

  std::string filename = argv[1];

  {
    std::ifstream file(filename);

    if (!file.is_open())
    {
      std::cerr << "Error: file is missing.\n";
      return 3;
    }

    file.close();
  }

  std::ifstream file(filename);

  std::vector< Polygon > data;

  while (!file.eof())
  {
    std::copy(
      std::istream_iterator< Polygon >(file),
      std::istream_iterator< Polygon >(),
      std::back_inserter(data)
    );

    gudkov::clearStream(file);
  }

  gudkov::iofmtguard fmtguardIn(std::cin);
  std::cin.unsetf(std::ios_base::skipws);

  gudkov::iofmtguard fmtguardOut(std::cout);
  std::cout.precision(1);
  std::cout.setf(std::ios_base::fixed);

  while (!std::cin.eof())
  {
    std::string command;
    std::string subcommand;

    try
    {
      command = gudkov::readCommand();
      subcommand = gudkov::readSubcommand(command);
      if (std::cin)
      {
        gudkov::doCommand(data, command, subcommand);
      }
      else
      {
        gudkov::clearStream(file);
      }
    }
    catch (const std::exception &exception)
    {
      gudkov::error();
    }
  }

  return 0;
}
