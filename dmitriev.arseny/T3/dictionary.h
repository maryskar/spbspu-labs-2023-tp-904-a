#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <map>
#include <string>
#include <functional>
#include "commands.h"

namespace dmitriev
{
  class CommandsDictionaty
  {
  public:
    CommandsDictionaty();

    void doCommand(const std::string& cmd,
      const polygons& data,
      std::ostream& out) const;

    void doCommand(const std::string& cmd,
      const polygons& data,
      size_t num,
      std::ostream& out) const;

    void doCommand(const std::string& cmd,
      const polygons& data,
      const Polygon& pol,
      std::ostream& out) const;

  private:
    using FirstType = std::function< void(const polygons&, std::ostream&) >;
    using SecondType = std::function< void(const polygons&, size_t, std::ostream&) >;
    using ThirdType = std::function< void(const polygons&, const polygon&, std::ostream&) >;


    std::map< std::string, FirstType > dictFirst;
    std::map< std::string, SecondType > dictSecond;
    std::map< std::string, ThirdType > dictThird;
  };

  std::ostream& printInvalidCommand(std::ostream& out);
  void runCommand(const polygons& data,
    const CommandsDictionaty& dict,
    std::ostream& out,
    std::istream& in);
}

#endif
