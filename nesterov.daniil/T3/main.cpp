#include <iostream>
#include <deque>
#include <iterator>
#include <map>
#include <limits>
#include <fstream>
#include "Polygon.h"
#include "CommandHandler.h"

void skipUntilNewLine(std::istream &in);

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Arguments are not correct!" << '\n';
    return 1;
  }
  std::ifstream input(argv[1]);

  using namespace nesterov;

  std::deque< Polygon > polygons;
  while (!input.eof())
  {
    std::copy(
      std::istream_iterator< Polygon >(input),
      std::istream_iterator< Polygon >(),
      std::back_inserter(polygons)
    );
    if (input.fail())
    {
      input.clear();
      skipUntilNewLine(input);
    }
  }

  std::map< std::string, const_cmd_t > const_cmds{
    {"AREA",   executeAreaCommand},
    {"MAX",    executeMaxCommand},
    {"MIN",    executeMinCommand},
    {"COUNT",  executeCountCommand},
    {"MAXSEQ", executeMaxSeqCommand}
  };

  std::map< std::string, cmd_t > cmds{
    {"ECHO", executeEchoCommand}
  };

  std::istream &cmdinput = std::cin;
  while (!cmdinput.eof())
  {
    std::string cmd;
    cmdinput >> cmd;
    if (cmd.empty())
    {
      continue;
    }

    try
    {
      try
      {
        auto toexecute = const_cmds.at(cmd);
        toexecute(polygons, cmdinput, std::cout);
      }
      catch (...)
      {
        auto toexecute = cmds.at(cmd);
        toexecute(polygons, cmdinput, std::cout);
      }
    }
    catch (...)
    {
      cmdinput.clear();
      skipUntilNewLine(cmdinput);
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}

void skipUntilNewLine(std::istream &in)
{
  auto maxstream = std::numeric_limits< std::streamsize >::max();
  in.ignore(maxstream, '\n');
}
