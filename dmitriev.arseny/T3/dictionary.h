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
    using type1 = std::function< void(const polygons&, std::ostream&) >;
    using type2 = std::function< void(const polygons&, size_t, std::ostream&) >;
    using type3 = std::function< void(const polygons&, const polygon&, std::ostream&) >;


    std::map< std::string, type1 > dictFirst;
    std::map< std::string, type2 > dictSecond;
    std::map< std::string, type3 > dictThird;
  };

  std::ostream& printInvalidCommand(std::ostream& out);
  std::string getCommand(std::istream& in);
  void runCommand(const polygons& data,
    const CommandsDictionaty& dict,
    std::ostream& out,
    std::istream& in);
}

#endif
