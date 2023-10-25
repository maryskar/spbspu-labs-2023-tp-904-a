#include "Commands.h"
#include <map>
#include "cmdRealisation.h"
timofeev::input timofeev::setCommand()
{
  timofeev::input command;
  command["Create"] = doCreateDict;
  command["Help"] = doPrintHelp;
  command["AddWord"] = doAddWord;
  command["Exist"] = doExist;
  command["DeleteT"] = doDeleteT;
  command["Delete"] = doDelete;
  command["Print"] = doPrint;
  command["Translate"] = doTranslate;
  command["Common"] = doCommon;
  return command;
}
