#ifndef T3_HELPERS_HPP
#define T3_HELPERS_HPP
#include <map>
#include "polygon.hpp"
namespace litvin
{
  class CommandDicts
  {
   public:
    CommandDicts();
    void executeCommand(const std::string & cmd,
        const std::vector< Polygon > & data,
        std::ostream & out) const;
    void executeCommand(const std::string & cmd,
        const std::vector< Polygon > & data,
        const Polygon & pol,
        std::ostream & out) const;
    void executeCommand(const std::string & cmd,
        const std::vector< Polygon > & data,
        size_t num,
        std::ostream & out) const;
   private:
    using signature_type_1 = void (*)(const std::vector< Polygon > & data, std::ostream & out);
    using signature_type_2 = void (*)(const std::vector< Polygon > & data, const Polygon & pol, std::ostream & out);
    using signature_type_3 = void (*)(const std::vector< Polygon > & data, size_t num, std::ostream & out);
    std::map< std::string, signature_type_1 > dict1;
    std::map< std::string, signature_type_2 > dict2;
    std::map< std::string, signature_type_3 > dict3;
  };
  std::ostream & printInvalidCommand(std::ostream & out);
  std::string inputCommand(std::istream & in);
  void runCommand(const std::vector< Polygon > & data,
      const CommandDicts & dicts,
      const std::string & cmd,
      std::ostream & out,
      std::istream & in);
}
#endif
