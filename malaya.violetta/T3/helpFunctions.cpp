#include "helpFunctions.hpp"
#include <iostream>
#include <vector>
#include "Polygon.hpp"
#include "commandFunctions.hpp"

namespace malaya
{
  std::string inputCommand(std::istream & in)
  {
    std::string command = " ";
    in >> command;
    return command;
  }
  void invalidPrint(std::ostream & out)
  {
    out << "<INVALID COMMAND>" << '\n';
  }
  void doCommand(const std::vector< Polygon > & data, std::string & command, std::istream & in,
                 std::ostream & out)
  {
    if(command == "AREA")
    {
      std::string option = " ";
      in >> option;
      if(option == "EVEN")
      {
        outAreaEven(data, out);
      }
      else if(option == "ODD")
      {
        outAreaOdd(data, out);
      }
      else if(option == "MEAN")
      {
        outMeanArea(data, out);
      }
      else
      {
        unsigned long long number = std::stoull(option);
        if(number < 3)
        {
          invalidPrint(out);
        }
        else
        {
          outAreaNum(data, number, out);
        }
      }
    }
    else if(command == "MAX")
    {
      std::string option = " ";
      in >> option;
      if(option == "AREA")
      {
        outMaxArea(data, out);
      }
      else if(option == "AREA")
      {
        outMaxVertexes(data, out);
      }
      else
      {
        invalidPrint(out);
      }
    }
    else if(command == "MIN")
    {
      std::string option = " ";
      in >> option;
      if(option == "AREA")
      {
        outMinArea(data, out);
      }
      else if(option == "AREA")
      {
        outMinVertexes(data, out);
      }
      else
      {
        invalidPrint(out);
      }
    }
    else if(command == "COUNT")
    {
      std::string option = " ";
      in >> option;
      if(option == "EVEN")
      {
        outCountEven(data, out);
      }
      else if(option == "ODD")
      {
        outCountOdd(data, out);
      }
      else
      {
        unsigned long long number = std::stoull(option);
        if(number < 3)
        {
          invalidPrint(out);
        }
        else
        {
          outCountNum(data, number, out);
        }
      }
    }
    else if(command == "PERMS")
    {
      Polygon polygon;
      in >> polygon;
      if(!in)
      {
        invalidPrint(out);
        return;
      }
      perms(data, out, polygon);
    }
    else if(command == "RECTS")
    {
      rects(data, out);
    }
    else
    {
      invalidPrint(out);
      in.setstate(std::ios::failbit);
    }
  }
}