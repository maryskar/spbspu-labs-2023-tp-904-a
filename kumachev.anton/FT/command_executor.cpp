#include "command_executor.h"
#include <istream>
#include <iterator>

kumachev::CommandExecutor::CommandExecutor(std::istream &istream, std::ostream &ostream, State &state,
    bool interactive):
  istream_(istream),
  ostream_(ostream),
  state_(state),
  interactive_(interactive)
{
  commands_["help"] = CommandExecutor::processHelp;
  commands_["dicts"] = CommandExecutor::processDicts;
  commands_["create"] = CommandExecutor::processCreate;
  commands_["load"] = CommandExecutor::processLoad;
  commands_["save_overwrite"] = CommandExecutor::processSaveOverwrite;
  commands_["save"] = CommandExecutor::processSave;
  commands_["add"] = CommandExecutor::processAdd;
  commands_["clear"] = CommandExecutor::processClear;
  commands_["translate_word"] = CommandExecutor::processTranslate;
  commands_["execute"] = CommandExecutor::processExecute;
  commands_["merge"] = CommandExecutor::processMerge;
  commands_["subtract"] = CommandExecutor::processSubtract;
}

void kumachev::CommandExecutor::execute()
{
  while (!istream_.eof()) {
    if (interactive_) {
      ostream_ << "> ";
    }

    std::string cmd;
    istream_ >> cmd;

    if (!interactive_) {
      ostream_ << cmd << '\n';
    }

    process(std::move(cmd));

    if (istream_.fail() && !istream_.eof()) {
      istream_.clear();
    }

    istream_.ignore(SKIP_MAX, '\n');
  }
}

void kumachev::CommandExecutor::process(std::string &&cmd)
{
  const auto &searchResult = commands_.find(cmd);

  if (searchResult != commands_.end()) {
    searchResult->second(*this);
  } else {
    istream_.setstate(std::ios::failbit);
    ostream_ << "Команда не найдена, введите help для получения помощи\n\n";
  }
}

void kumachev::CommandExecutor::processHelp(CommandExecutor &executor)
{
  executor.ostream_ << "Список команд:\n"
                    << "\t1. help - вывести это сообщение\n"
                    << "\t2. dicts - список словарей\n"
                    << "\t3. create <dict> - создать пустой словарь\n"
                    << "\t4. load <dict> <path> - загрузить словарь с диска\n"
                    << "\t5. save <dict> <path> - сохранить на диск\n"
                    << "\t\t5.1. save overwrite <dict> <path> - сохранить на диск + перезаписать при необходимости\n"
                    << "\t6. add <dict> <english> <russian>... - добавить слово в словарь\n"
                    << "\t7. clear <dict> - удалить все элементы из словаря\n"
                    << "\t8. translate_word <dict> <english> - вывести список переводов слова\n"
                    << "\t9. execute <script> - выполнить скрипт, состоящий из представленных команд\n"
                    << "\t10. merge <dict_out> <dict1> <dict2> - объединить словари <dict1> и <dict2> в словарь <dict_out>\n"
                    << "\t11. subtract <dict_out> <dict1> <dict2> - вычесть словарь <dict2> из <dict1>"
                    << " и записать результат в <dict_out>\n\n";
}

void kumachev::CommandExecutor::processDicts(CommandExecutor &executor)
{
  bool any = false;

  for (const auto &dict: executor.state_.dicts) {
    executor.ostream_ << dict.first << '\n';
    any = true;
  }

  if (!any) {
    executor.ostream_ << "<пусто>\n";
  }

  executor.ostream_ << '\n';
}

void kumachev::CommandExecutor::processCreate(CommandExecutor &executor)
{
  std::istream &istream = executor.istream_;
  std::ostream &ostream = executor.ostream_;
  State &state = executor.state_;

  std::string dictName;
  istream >> dictName;

  if (istream.fail()) {
    ostream << "Ошибка в синтаксисе команды, введите help для получения справки\n\n";
    return;
  }

  if (state.dicts.find(dictName) == state.dicts.end()) {
    state.dicts[dictName] = EnglishRussianDictionary();
  } else {
    ostream << "ОШИБКА: Словарь с таким именем уже существует\n\n";
  }
}

void kumachev::CommandExecutor::processLoad(CommandExecutor &executor)
{

}

void kumachev::CommandExecutor::processSave(CommandExecutor &executor)
{

}

void kumachev::CommandExecutor::processSaveOverwrite(CommandExecutor &executor)
{

}

void kumachev::CommandExecutor::processAdd(CommandExecutor &executor)
{
  std::istream &istream = executor.istream_;
  std::ostream &ostream = executor.ostream_;
  State &state = executor.state_;

  std::string dictName;
  std::string english;
  std::vector< std::string > russian;
  istream >> dictName >> english;

  std::string nextRussian;
  char nextChar = '\0';
  istream.get(nextChar);

  while (nextChar != '\n') {
    if (nextChar != ' ') {
      nextRussian.push_back(nextChar);
    } else {
      if (nextRussian.length() != 0) {
        russian.push_back(nextRussian);
        nextRussian = "";
      }
    }

    istream.get(nextChar);
  }

  if (nextRussian.length() != 0) {
    russian.push_back(nextRussian);
  }

  istream.putback('\n');

  if (istream.fail() || russian.empty()) {
    ostream << "Ошибка в синтаксисе команды, введите help для получения справки\n\n";
    return;
  }

  const auto &searchResult = state.dicts.find(dictName);

  if (searchResult == state.dicts.end()) {
    ostream << "ОШИБКА: Словарь не найден\n\n";
    return;
  }

  searchResult->second.add(english, russian.begin(), russian.end());
}

void kumachev::CommandExecutor::processClear(CommandExecutor &executor)
{
  std::istream &istream = executor.istream_;
  std::ostream &ostream = executor.ostream_;
  State &state = executor.state_;

  std::string dictName;
  istream >> dictName;

  if (istream.fail()) {
    ostream << "Ошибка в синтаксисе команды, введите help для получения справки\n\n";
    return;
  }

  const auto &searchResult = state.dicts.find(dictName);
  if (searchResult == state.dicts.end()) {
    ostream << "ОШИБКА: Словарь не найден\n\n";
    return;
  } else {
    searchResult->second.clear();
  }
}

void kumachev::CommandExecutor::processTranslate(CommandExecutor &executor)
{
  std::istream &istream = executor.istream_;
  std::ostream &ostream = executor.ostream_;
  State &state = executor.state_;

  std::string dictName;
  std::string english;
  istream >> dictName >> english;

  if (istream.fail()) {
    ostream << "Ошибка в синтаксисе команды, введите help для получения справки\n\n";
    return;
  }

  const auto &searchResult = state.dicts.find(dictName);

  if (searchResult == state.dicts.end()) {
    ostream << "ОШИБКА: Словарь не найден\n\n";
    return;
  }

  try {
    const auto &translated = searchResult->second.translate(english);
    for (const auto &word: translated) {
      ostream << word << '\n';
    }

    ostream << '\n';
  }
  catch (const WordNotFound &) {
    ostream << "ОШИБКА: слово отсутствует в словаре\n\n";
  }
}

void kumachev::CommandExecutor::processExecute(CommandExecutor &executor)
{

}

void kumachev::CommandExecutor::processMerge(CommandExecutor &executor)
{

}

void kumachev::CommandExecutor::processSubtract(CommandExecutor &executor)
{

}
