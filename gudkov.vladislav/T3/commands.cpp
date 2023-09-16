#include "commands.h"
#include <exception>
#include <iostream>

std::string gudkov::readCommand()
{
  std::string command = "";
  std::cin >> gudkov::LabelIO{ command };
  std::cin >> gudkov::DelimiterExpIO{ ' ' };

  if (!std::cin)
  {
    if (!std::cin.eof())
    {
      throw std::runtime_error("Invalid command.\n");
    }
  }

  checkCommand(command);

  return command;
}

void gudkov::checkCommand(const std::string &command)
{
  if (command == "AREA")
  {
    return;
  }
  if (command == "MAX")
  {
    return;
  }
  if (command == "MIN")
  {
    return;
  }
  if (command == "COUNT")
  {
    return;
  }
  if (command == "PERMS")
  {
    return;
  }
  if (command == "LESSAREA")
  {
    return;
  }

  throw std::runtime_error("Wrong command.\n");
}

std::string gudkov::readSubcommand()
{
  std::string subcommand = "";
  std::cin >> gudkov::LabelIO{ subcommand };
  std::cin >> gudkov::DelimiterExpIO{ '\n' };

  return subcommand;
}

std::string gudkov::readSubcommand(const std::string &command)
{
  std::string subcommand = "";

  if (command == "AREA")
  {
    subcommand = gudkov::readSubcommand();
  }
  else if (command == "MAX")
  {
    subcommand = gudkov::readSubcommand();
  }
  else if (command == "MIN")
  {
    subcommand = gudkov::readSubcommand();
  }
  else if (command == "COUNT")
  {
    subcommand = gudkov::readSubcommand();
  }
  else if (command == "PERMS")
  {

  }
  else if (command == "LESSAREA")
  {

  }

  checkSumcommand(command, subcommand);

  return subcommand;
}

void gudkov::checkSumcommand(const std::string &command, const std::string &subcommand)
{
  if (command == "AREA")
  {
    if (subcommand == "EVEN")
    {
      return;
    }
    if (subcommand == "ODD")
    {
      return;
    }
    if (subcommand == "MEAN")
    {
      return;
    }

    checkForNumber(subcommand);

    return;
  }
  else if (command == "MAX")
  {
    if (subcommand == "AREA")
    {
      return;
    }
    else if (subcommand == "VERTEXES")
    {
      return;
    }
  }
  else if (command == "MIN")
  {
    if (subcommand == "AREA")
    {
      return;
    }
    else if (subcommand == "VERTEXES")
    {
      return;
    }
  }
  else if (command == "COUNT")
  {
    if (subcommand == "EVEN")
    {
      return;
    }
    if (subcommand == "ODD")
    {
      return;
    }

    checkForNumber(subcommand);

    return;
  }
  else if (command == "PERMS")
  {
    return;
  }
  else if (command == "LESSAREA")
  {
    return;
  }

  throw std::runtime_error("Invalid subcommand.\n");
}

void gudkov::checkForNumber(const std::string &str)
{
  const std::runtime_error exception("Invalid number.\n");

  size_t countOfProceedSymbols = 0;
  try
  {
    std::stoi(str, &countOfProceedSymbols);
  }
  catch (const std::invalid_argument &exception)
  {
    throw exception;
  }
  catch (const std::out_of_range &exception)
  {
    throw exception;
  }

  if (countOfProceedSymbols != str.size())
  {
    throw exception;
  }
}

void gudkov::doArea(const std::vector< Polygon > &data, const std::string &subcommand)
{
  if (subcommand == "EVEN")
  {
    std::cout << areaEven(data) << std::endl;
    return;
  }
  if (subcommand == "ODD")
  {
    std::cout << areaOdd(data) << std::endl;
    return;
  }
  if (subcommand == "MEAN" && !data.empty())
  {
    std::cout << areaMean(data) << std::endl;
    return;
  }

  size_t countOfProceedSymbols = 0;
  int vertexesNum = std::stoi(subcommand, &countOfProceedSymbols);

  if (countOfProceedSymbols != subcommand.size())
  {
    throw std::runtime_error("Invalid number.\n");
  }

  std::cout << areaVertexes(data, vertexesNum) << std::endl;
}

void gudkov::max(const std::vector< Polygon > &data, const std::string &subcommand)
{
  if (!data.empty())
  {
    if (subcommand == "AREA")
    {
      std::cout << maxArea(data) << std::endl;
      return;
    }
    else if (subcommand == "VERTEXES")
    {
      std::cout << maxVertexes(data) << std::endl;
      return;
    }
  }

  throw std::runtime_error("Polygons are missing.\n");
}

void gudkov::min(const std::vector< Polygon > &data, const std::string &subcommand)
{
  if (!data.empty())
  {
    if (subcommand == "AREA")
    {
      std::cout << minArea(data) << std::endl;
      return;
    }
    else if (subcommand == "VERTEXES")
    {
      std::cout << minVertexes(data) << std::endl;
      return;
    }
  }

  throw std::runtime_error("Polygons are missing.\n");
}

void gudkov::count(const std::vector< Polygon > &data, const std::string &subcommand)
{
  if (subcommand == "EVEN")
  {
    std::cout << countEven(data) << std::endl;
    return;
  }
  if (subcommand == "ODD")
  {
    std::cout << countOdd(data) << std::endl;
    return;
  }

  int vertexesNum = std::stoi(subcommand);
  std::cout << countVertexes(data, vertexesNum) << std::endl;
}

void gudkov::perms(const std::vector< Polygon > &data)
{
  gudkov::Polygon input;
  std::cin >> input;

  if (std::cin)
  {
    std::cout << permutations(data, input) << std::endl;
    return;
  }

  throw std::runtime_error("Invalid polygon.\n");
}

void gudkov::lessarea(const std::vector< Polygon > &data)
{
  gudkov::Polygon input;
  std::cin >> input;

  if (std::cin)
  {
    std::cout << lessArea(data, input) << std::endl;
    return;
  }

  throw std::runtime_error("Invalid polygon.\n");
}

void gudkov::doCommand(const std::vector< Polygon > &data, const std::string &command, const std::string &subcommand)
{
  if (command == "AREA")
  {
    gudkov::doArea(data, subcommand);
  }
  else if (command == "MAX")
  {
    gudkov::max(data, subcommand);
  }
  else if (command == "MIN")
  {
    gudkov::min(data, subcommand);
  }
  else if (command == "COUNT")
  {
    gudkov::count(data, subcommand);
  }
  else if (command == "PERMS")
  {
    gudkov::perms(data);
  }
  else if (command == "LESSAREA")
  {
    gudkov::lessarea(data);
  }
}

void gudkov::error()
{
  if (!std::cin.eof())
  {
    std::cerr << "<INVALID COMMAND>" << std::endl;

    gudkov::clearStream(std::cin);
  }
}
