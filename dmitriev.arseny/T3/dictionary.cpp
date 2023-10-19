#include "dictionary.h"
#include <customtypes.h>

dmitriev::CommandsDictionaty::CommandsDictionaty()
{
  dictFirst["AREA EVEN"] = printEvenArea;
  dictFirst["AREA ODD"] = printOddArea;
  dictFirst["AREA MEAN"] = printMeanArea;
  dictFirst["MAX AREA"] = printMaxArea;
  dictFirst["MIN AREA"] = printMinArea;
  dictFirst["MAX VERTEXES"] = printMaxSize;
  dictFirst["MIN VERTEXES"] = printMinSize;
  dictFirst["COUNT EVEN"] = printEvenSizeCount;
  dictFirst["COUNT ODD"] = printOddSizeCount;

  dictSecond["COUNT"] = printNSizeCount;
  dictSecond["AREA"] = printNSizeArea;

  dictThird["INFRAME"] = printInFrame;
  dictThird["SAME"] = printSame;
}

void dmitriev::CommandsDictionaty::doCommand(const std::string& cmd,
  const polygons& data,
  std::ostream& out) const
{
  FirstType function = dictFirst.at(cmd);
  function(data, out);
}

void dmitriev::CommandsDictionaty::doCommand(const std::string& cmd,
  const polygons & data,
  size_t num,
  std::ostream & out) const
{
  SecondType function = dictSecond.at(cmd);
  function(data, num, out);
}

void dmitriev::CommandsDictionaty::doCommand(const std::string& cmd,
  const polygons& data,
  const Polygon& pol,
  std::ostream& out) const
{
 ThirdType function = dictThird.at(cmd);
 function(data, pol, out);
}

std::ostream& dmitriev::printInvalidCommand(std::ostream& out)
{
  return out << "<INVALID COMMAND>";
}

bool isSpecialCommand(std::string name)
{
  return name == "INFRAME" || name == "SAME";
}
bool isBasicCommand(std::string name)
{
  return name == "MAX" || name == "MIN" || name == "AREA" || name == "COUNT";
}

std::string getCommand(std::istream& in)
{
  std::string cmdName = "";
  in >> cmdName;
  if (!in)
  {
    throw std::runtime_error("problems with input");
  }

  if (!isSpecialCommand(cmdName))
  {
    if (isBasicCommand(cmdName))
    {
      std::string cmdSubName = "";
      in >> cmdSubName;
      if (!in)
      {
        std::invalid_argument("invalid command parameter");
      }
      cmdName += " " + cmdSubName;
    }
    else
    {
      throw std::invalid_argument("invalid command name");
    }
  }

  return cmdName;
}

void dmitriev::runCommand(const polygons& data,
  const CommandsDictionaty& dict,
  std::ostream& out,
  std::istream& in)
{
  std::string cmdName = getCommand(in);
  if (isSpecialCommand(cmdName))
  {
    polygon figure;
    in >> figure >> SeparatorIO{'\n'};
    if (!in)
    {
      throw std::invalid_argument("Invalid command parameter");
    }
    dict.doCommand(cmdName, data, figure, out);
    out << '\n';
    return;
  }
  try
  {
    dict.doCommand(cmdName, data, out);
    out << '\n';
    return;
  }
  catch (const std::out_of_range&)
  {}
  size_t pos = cmdName.find(' ');
  size_t num = std::stoull(cmdName.substr(pos));
  dict.doCommand(cmdName.substr(0, pos), data, num, out);
  out << '\n';
}
