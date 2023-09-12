#include "Commands.h"
#include <map>
namespace setCommands
{
  void command(input& command)
  {
    command["Help"] = printHelp;
    command["RusAddWord"] = RusAddWord;
    command["EngAddWord"] = EngAddWord;
    command["Exist"] = Exist;
    command["EngDelWord"] = Eng;
    command["DeleteAll"] = DeleteAll;
    command["RuPrint"] = RuPrint;
    command["EngPrint"] = EngPrint;
    command["AllPrint"] = AllPrint;
  }
}