#include "command_executor.h"
#include <istream>
#include <sstream>
#include <iterator>

kumachev::CommandExecutor::CommandExecutor(std::istream &istream, std::ostream &ostream, State &state,
    bool interactive):
  istream_(istream),
  ostream_(ostream),
  state_(state),
  interactive_(interactive)
{}

void kumachev::CommandExecutor::execute()
{
  while (!istream_.eof()) {
    if (interactive_) {
      ostream_ << "> ";
    }

    std::string cmd;
    std::getline(istream_, cmd, '\n');

    if (!interactive_) {
      ostream_ << cmd << '\n';
    }

    if (cmd == "exit") {
      ostream_ << "Bye\n";
      break;
    }

    process(std::move(cmd));

    if (!istream_) {
      istream_.clear();
    }
  }
}

void kumachev::CommandExecutor::process(std::string &&cmd)
{
  if (cmd == "help") {
    processHelp();
  } else if (cmd == "dicts") {
    processDicts();
  } else if (cmd.find("create") == 0) {
    processCreate(std::move(cmd));
  } else if (cmd.find("load") == 0) {
    processLoad(std::move(cmd));
  } else if (cmd.find("save overwrite") == 0) {
    processSaveOverwrite(std::move(cmd));
  } else if (cmd.find("save") == 0) {
    processSave(std::move(cmd));
  } else if (cmd.find("add") == 0) {
    processAdd(std::move(cmd));
  } else if (cmd.find("clear") == 0) {
    processClear(std::move(cmd));
  } else if (cmd.find("translate_word") == 0) {
    processTranslate(std::move(cmd));
  } else if (cmd.find("execute") == 0) {
    processExecute(std::move(cmd));
  } else if (cmd.find("merge") == 0) {
    processMerge(std::move(cmd));
  } else if (cmd.find("subtract") == 0) {
    processSubtract(std::move(cmd));
  } else {
    ostream_ << "Команда не найдена, введите help для получения помощи\n\n";
    istream_.setstate(std::ios::failbit);
  }
}

void kumachev::CommandExecutor::processHelp()
{
  ostream_ << "Список команд:\n"
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

void kumachev::CommandExecutor::processDicts()
{
  bool any = false;

  for (const auto &dict: state_.dicts) {
    ostream_ << dict.first << '\n';
    any = true;
  }

  if (!any) {
    ostream_ << "<пусто>\n";
  }

  ostream_ << '\n';
}

void kumachev::CommandExecutor::processCreate(std::string &&cmd)
{
  std::stringstream cmdStream(cmd);
  std::istream::sentry sentry(cmdStream);

  if (!sentry) {
    return;
  }

  cmdStream.ignore(SKIP_MAX, ' ');

  std::string dictName;
  cmdStream >> dictName;

  if (cmdStream.fail() || !cmdStream.eof()) {
    ostream_ << "Ошибка в синтаксисе команды, введите help для получения справки\n\n";
    return;
  }

  if (state_.dicts.find(dictName) == state_.dicts.end()) {
    state_.dicts[dictName] = Dictionary();
  } else {
    ostream_ << "ОШИБКА: Словарь с таким именем уже существует\n\n";
  }
}

void kumachev::CommandExecutor::processLoad(std::string &&cmd)
{

}

void kumachev::CommandExecutor::processSave(std::string &&cmd)
{

}

void kumachev::CommandExecutor::processSaveOverwrite(std::string &&cmd)
{

}

void kumachev::CommandExecutor::processAdd(std::string &&cmd)
{
  std::stringstream cmdStream(cmd);
  std::istream::sentry sentry(cmdStream);

  if (!sentry) {
    return;
  }

  cmdStream.ignore(SKIP_MAX, ' ');

  std::string dictName;
  std::string english;
  std::vector< std::string > russian;
  auto backInserter = std::back_inserter(russian);
  cmdStream >> dictName >> english;

  std::copy(
    std::istream_iterator< std::string >(cmdStream),
    std::istream_iterator< std::string >(),
    backInserter
  );

  if (!cmdStream.eof() || russian.empty()) {
    ostream_ << "Ошибка в синтаксисе команды, введите help для получения справки\n\n";
    return;
  }

  const auto &searchResult = state_.dicts.find(dictName);

  if (searchResult == state_.dicts.end()) {
    ostream_ << "ОШИБКА: Словарь не найден\n\n";
    return;
  }

  searchResult->second.add(english, russian.begin(), russian.end());
}

void kumachev::CommandExecutor::processClear(std::string &&cmd)
{
  std::stringstream cmdStream(cmd);
  std::istream::sentry sentry(cmdStream);

  if (!sentry) {
    return;
  }

  cmdStream.ignore(SKIP_MAX, ' ');

  std::string dictName;
  cmdStream >> dictName;

  if (cmdStream.fail() || !cmdStream.eof()) {
    ostream_ << "Ошибка в синтаксисе команды, введите help для получения справки\n\n";
    return;
  }

  const auto &searchResult = state_.dicts.find(dictName);
  if (searchResult == state_.dicts.end()) {
    ostream_ << "ОШИБКА: Словарь не найден\n\n";
    return;
  } else {
    searchResult->second.clear();
  }
}

void kumachev::CommandExecutor::processTranslate(std::string &&cmd)
{
  std::stringstream cmdStream(cmd);
  std::istream::sentry sentry(cmdStream);

  if (!sentry) {
    return;
  }

  cmdStream.ignore(SKIP_MAX, ' ');

  std::string dictName;
  std::string english;
  cmdStream >> dictName >> english;

  if (cmdStream.fail() || !cmdStream.eof()) {
    ostream_ << "Ошибка в синтаксисе команды, введите help для получения справки\n\n";
    return;
  }

  const auto &searchResult = state_.dicts.find(dictName);

  if (searchResult == state_.dicts.end()) {
    ostream_ << "ОШИБКА: Словарь не найден\n\n";
    return;
  }

  try {
    const auto &translated = searchResult->second.translate(english);
    for (const auto &word: translated) {
      ostream_ << word << '\n';
    }

    ostream_ << '\n';
  }
  catch (const WordNotFound &) {
    ostream_ << "ОШИБКА: слово отсутствует в словаре\n\n";
  }
}

void kumachev::CommandExecutor::processExecute(std::string &&cmd)
{

}

void kumachev::CommandExecutor::processMerge(std::string &&cmd)
{

}

void kumachev::CommandExecutor::processSubtract(std::string &&cmd)
{

}
