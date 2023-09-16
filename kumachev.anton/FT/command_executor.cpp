#include "command_executor.h"
#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <fstream>
#include "dictionary_io.h"

namespace kumachev {
  using dict_map_pair = std::pair< const std::string, er_dictionary >;

  static std::string getDictName(const dict_map_pair &pair)
  {
    return pair.first;
  }

  static bool isNotInDict(const er_pair &pair, const er_dictionary &dict)
  {
    return dict.find(pair.first) == dict.cend();
  }

  static bool doesFileExist(const std::string &path)
  {
    std::ifstream checkFile(path);
    return checkFile.is_open();
  }

  static void printHelp(std::ostream &ostream);

  static void handleDicts(State &state, string_vector &args,
      std::ostream &ostream);

  static void handleCreate(State &state, string_vector &args,
      std::ostream &ostream);

  static void handleLoad(State &state, string_vector &args,
      std::ostream &ostream);

  static void handleSave(State &state, string_vector &args,
      std::ostream &ostream);

  static void handleAdd(State &state, string_vector &args,
      std::ostream &ostream);

  static void handleClear(State &state, string_vector &args,
      std::ostream &ostream);

  static void handleTranslate(State &st, string_vector &args,
      std::ostream &ostream);

  static void handleExecute(State &state, string_vector &args,
      std::ostream &ostream);

  static void handleMerge(State &state, string_vector &args,
      std::ostream &ostream);

  static void handleSubtract(State &st, string_vector &args,
      std::ostream &ostream);

  CommandExecutor::CommandExecutor(std::istream &istream,
      std::ostream &ostream, const CommandSystem &commandSystem, State &state):
    istream_(istream),
    ostream_(ostream),
    commandSystem_(commandSystem),
    state_(state)
  {
  }

  void CommandExecutor::handleCommand()
  {
    std::string line, command;

    std::getline(istream_, line, '\n');

    if (line.empty()) {
      return;
    }

    if (line.find("help") == 0) {
      printHelp(ostream_);
      return;
    }

    size_t spcIndex = line.find(' ');
    std::vector< std::string > args;

    if (spcIndex == std::string::npos) {
      command = line;
    } else {
      command = line.substr(0, spcIndex);
      size_t index = line.find(' ', spcIndex + 1);

      while (index != std::string::npos) {
        std::string argument = line.substr(spcIndex + 1, index - spcIndex - 1);

        if (!argument.empty()) {
          args.push_back(argument);
        }

        spcIndex = index;
        index = line.find(' ', spcIndex + 1);
      }

      // Get last argument
      std::string argument = line.substr(spcIndex + 1);

      if (!argument.empty()) {
        args.push_back(argument);
      }
    }

    try {
      const auto &handler = commandSystem_.handlers.at(command);
      handler(state_, args, ostream_);
    }
    catch (const std::out_of_range &e) {
      ostream_ << "Команда не найдена\n";
      return;
    }
  }

  CommandSystem createCommandSystem()
  {
    CommandSystem commandSystem;
    commandSystem.handlers["dicts"] = handleDicts;
    commandSystem.handlers["create"] = handleCreate;
    commandSystem.handlers["load"] = handleLoad;
    commandSystem.handlers["save"] = handleSave;
    commandSystem.handlers["add"] = handleAdd;
    commandSystem.handlers["clear"] = handleClear;
    commandSystem.handlers["translate_word"] = handleTranslate;
    commandSystem.handlers["execute"] = handleExecute;
    commandSystem.handlers["merge"] = handleMerge;
    commandSystem.handlers["subtract"] = handleSubtract;

    return commandSystem;
  }

  void printHelp(std::ostream &ostream)
  {
    ostream << "Список команд:\n"
            << "\t1. help - вывести это сообщение\n"
            << "\t2. dicts - список словарей\n"
            << "\t3. create <dict> - создать пустой словарь\n"
            << "\t4. load <dict> <path> - загрузить словарь с диска\n"
            << "\t5. save <dict> <path> - сохранить на диск\n"
            << "\t\t5.1. save overwrite <dict> <path> - сохранить на диск +"
            << " перезаписать при необходимости\n"
            << "\t6. add <dict> <english> <russian>... - добавить"
            << "слово в словарь\n"
            << "\t7. clear <dict> - удалить все элементы из словаря\n"
            << "\t8. translate_word <dict> <english> - вывести"
            << " список переводов слова\n"
            << "\t9. execute <script> - выполнить скрипт,"
            << " состоящий из представленных команд\n"
            << "\t10. merge <dict_out> <dict1> <dict2> -"
            << " объединить словари <dict1> и <dict2> в словарь <dict_out>\n"
            << "\t11. subtract <dict_out> <dict1> <dict2> - вычесть"
            << "словарь <dict2> из <dict1> и записать"
            << " результат в <dict_out>\n\n";
  }

  void handleDicts(State &state, string_vector &args, std::ostream &ostream)
  {
    if (!args.empty()) {
      ostream << "Команда не принимает аргументы\n";
      return;
    }

    if (state.dicts.empty()) {
      ostream << "<пусто>\n";
    }

    std::vector< std::string > names;
    names.reserve(state.dicts.size());
    auto inserter = std::back_inserter(names);
    const auto &dicts = state.dicts;
    std::transform(dicts.cbegin(), dicts.cend(), inserter, getDictName);

    auto output = std::ostream_iterator< std::string >(ostream, "\n");
    std::copy(names.cbegin(), names.cend(), output);
  }

  void handleCreate(State &state, string_vector &args, std::ostream &ostream)
  {
    if (args.size() != 1) {
      ostream << "Команда принимает 1 аргумент\n";
      return;
    }

    std::string dictName = args[0];

    if (state.dicts.find(dictName) == state.dicts.end()) {
      state.dicts[dictName] = er_dictionary();
    } else {
      ostream << "ОШИБКА: Словарь с таким именем уже существует\n";
    }
  }

  void handleLoad(State &state, string_vector &args, std::ostream &ostream)
  {
    if (args.size() != 2) {
      ostream << "Команда принимает 2 аргумента\n";
      return;
    }

    std::string dictName = args[0];
    std::string path = args[1];

    if (state.dicts.find(dictName) != state.dicts.end()) {
      ostream << "ОШИБКА: Словарь с таким именем уже существует\n";
      return;
    }

    std::ifstream file(path);

    if (!file.good()) {
      ostream << "ОШИБКА: Не удалось открыть файл\n";
      return;
    }

    er_dictionary dict;
    file >> dict;

    if (!file.good()) {
      ostream << "ОШИБКА: Файл содержит данные некорректного формата\n";
      return;
    }

    state.dicts[dictName] = dict;
  }

  void handleSave(State &state, string_vector &args, std::ostream &ostream)
  {
    size_t argCount = args.size();

    if (argCount < 2 || argCount > 3) {
      ostream << "Команда принимает 2 или 3 аргумента\n";
      return;
    }

    std::string dictName, path;
    bool overwrite = false;

    if (argCount == 2) {
      dictName = args[0];
      path = args[1];
    } else {
      if (args[0] != "overwrite") {
        ostream << "Некорректный синтаксис команды\n";
        return;
      }

      dictName = args[1];
      path = args[2];
      overwrite = true;
    }

    auto searchResult = state.dicts.find(dictName);

    if (searchResult == state.dicts.end()) {
      ostream << "ОШИБКА: Словарь не найден\n";
      return;
    }

    if (doesFileExist(path) && !overwrite) {
      ostream << "ОШИБКА: Файл уже существует, используйте save overwrite "
              << "чтобы принудительно перезаписать его\n";

      return;
    }

    std::ofstream file(path);

    try {
      const er_dictionary & dict = searchResult->second;
      file << dict;
    } catch (const std::exception &) {
      ostream << "Не удалось сохранить словарь\n";
    }
  }

  void handleAdd(State &state, string_vector &args, std::ostream &ostream)
  {
    if (args.size() < 3) {
      ostream << "Команда принимает минимум 3 аргумента\n";
      return;
    }

    std::string dictName = args[0];
    std::string english = args[1];
    auto russianBegin = args.cbegin();
    std::advance(russianBegin, 2);

    std::vector< std::string > russianWords(russianBegin, args.cend());
    const auto &searchResult = state.dicts.find(dictName);

    if (searchResult == state.dicts.end()) {
      ostream << "ОШИБКА: Словарь не найден\n";
      return;
    }

    searchResult->second[english] = russianWords;
  }

  void handleClear(State &state, string_vector &args, std::ostream &ostream)
  {
    if (args.size() != 1) {
      ostream << "Команда принимает 1 аргумент\n";
      return;
    }

    std::string dictName = args[0];
    const auto &searchResult = state.dicts.find(dictName);

    if (searchResult == state.dicts.end()) {
      ostream << "ОШИБКА: Словарь не найде\n";
      return;
    }

    searchResult->second.clear();
  }

  void handleTranslate(State &st, string_vector &args, std::ostream &ostream)
  {
    if (args.size() != 2) {
      ostream << "Команда принимает 2 аргумента\n";
      return;
    }

    std::string dictName = args[0];
    std::string english = args[1];

    const auto &searchResult = st.dicts.find(dictName);

    if (searchResult == st.dicts.end()) {
      ostream << "ОШИБКА: Словарь не найден\n";
      return;
    }

    try {
      const auto &translated = searchResult->second.at(english);
      auto output = std::ostream_iterator< std::string >(ostream, "\n");
      std::copy(translated.cbegin(), translated.cend(), output);
    }
    catch (const std::out_of_range &) {
      ostream << "ОШИБКА: слово отсутствует в словаре\n";
    }
  }

  void handleExecute(State &state, string_vector &args, std::ostream &ostream)
  {
    if (args.size() != 1) {
      ostream << "Команда принимает 1 аргумент\n";
      return;
    }

    std::string path = args[0];
    std::ifstream script(path);

    if (!script.good()) {
      ostream << "ОШИБКА: Не удалось открыть файл скрипта\n";
      return;
    }

    kumachev::CommandSystem cs = kumachev::createCommandSystem();
    kumachev::CommandExecutor scriptExecutor(script, std::cout, cs, state);

    while (script.good()) {
        scriptExecutor.handleCommand();
    }
  }

  void handleMerge(State &state, string_vector &args, std::ostream &ostream)
  {
    if (args.size() != 3) {
      ostream << "Команда принимает 3 аргумента\n";
      return;
    }

    std::string resultDictName = args[0];
    std::string firstName = args[1];
    std::string secondName = args[2];

    er_dictionary result;
    const auto &first = state.dicts.find(firstName);
    const auto &second = state.dicts.find(secondName);

    if (first == state.dicts.end()) {
      ostream << "ОШИБКА: Словарь 1 не найден\n";
      return;
    }

    if (second == state.dicts.end()) {
      ostream << "ОШИБКА: Словарь 2 не найден\n";
      return;
    }

    result.insert(first->second.cbegin(), first->second.cend());
    result.insert(second->second.cbegin(), second->second.cend());
    state.dicts[resultDictName] = result;
  }

  void handleSubtract(State &st, string_vector &args, std::ostream &ostream)
  {
    using namespace std::placeholders;

    if (args.size() != 3) {
      ostream << "Команда принимает 3 аргумента\n";
      return;
    }

    std::string resultDictName = args[0];
    std::string firstName = args[1];
    std::string secondName = args[2];

    er_dictionary result;
    const auto &first = st.dicts.find(firstName);
    const auto &second = st.dicts.find(secondName);

    if (first == st.dicts.end()) {
      ostream << "ОШИБКА: Словарь 1 не найден\n";
      return;
    }

    if (second == st.dicts.end()) {
      ostream << "ОШИБКА: Словарь 2 не найден\n";
      return;
    }

    auto isNotInSecond = std::bind(isNotInDict, _1, second->second);
    std::vector< er_pair > subtractionResult;
    auto inserter = std::back_inserter(subtractionResult);
    auto cbegin = first->second.cbegin();
    auto cend = first->second.cend();

    std::copy_if(cbegin, cend, inserter, isNotInSecond);
    result.insert(subtractionResult.cbegin(), subtractionResult.cend());
    st.dicts[resultDictName] = result;
  }
}
