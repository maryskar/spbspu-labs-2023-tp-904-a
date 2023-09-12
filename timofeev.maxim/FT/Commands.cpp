#include "Commands.h"
#include <map>
#include "cmdRealisation.h"
namespace timofeev
{
  void command(input& command)
  {
    command["Help"] = printHelp;
    command["AddWord"] = AddWord;
    command["Exist"] = Exist;
    command["DeleteW"] = DeleteW;
    command["Delete"] = Delete;
    command["Print"] = Print;
    command["Translate"] = Translate;
    //command["Common"] = ?
  }


}