#ifndef COMMANDS_H
#define COMMANDS_H
#include <iostream>
#include <map>
#include "datastructs.h"

namespace azheganova
{
    using commands1 = void (*) (const std::vector< Polygon > & polygon, std::ostream & out);
    using commands2 = void (*) (const std::vector< Polygon > & polygon, size_t num, std::ostream & out);
    using commands3 = void(*)(const std::vector< Polygon > & polygon, std::ostream & out);
    struct Commands
    {
      std::map< std::string, commands1 > dict_1;
      std::map< std::string, commands2 > dict_2;
      std::map< std::string, commands3 > dict_3;
    };
    Commands createCommands();
    void getAreaEven(const std::vector< Polygon > & polygon, std::ostream & out);
    void getAreaOdd(const std::vector< Polygon > & polygon, std::ostream & out);
    void getAreaMean(const std::vector< Polygon > & polygon, std::ostream & out);
    void getAreaNumOfVertexes(const std::vector< Polygon > & polygon, size_t num, std::ostream & out);
    void getMaxArea(const std::vector< Polygon > & polygon, std::ostream & out);
    void getMaxVertexes(const std::vector< Polygon > & polygon, std::ostream & out);
    void getMinArea(const std::vector< Polygon > & polygon, std::ostream & out);
    void getMinVertexes(const std::vector< Polygon > & polygon, std::ostream & out);
    void countEven(const std::vector< Polygon > & polygon, std::ostream & out);
    void countOdd(const std::vector< Polygon > & polygon, std::ostream & out);
    void countNumOfVertexes(const std::vector< Polygon > & polygon, size_t num, std::ostream & out);
    void getRmecho(const std::vector< Polygon > & polygon, std::ostream & out);
    void getRightshapes(const std::vector< Polygon > & polygon, std::ostream & out);
}

#endif
