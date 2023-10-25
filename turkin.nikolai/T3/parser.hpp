#ifndef PARSER_HPP
#define PARSER_HPP

#include <deque>
#include <istream>
#include <ostream>

#include "commands-list.hpp"
#include "data-structs.hpp"
#include "sub-commands-list.hpp"

namespace turkin
{
  struct MakeCMD
  {
    public:
      MakeCMD();
      CommandsList & get_main();
      SubCommandsList & get_sub();
    private:
      CommandsList main_list_;
      SubCommandsList sub_list_;
  };
}

#endif
