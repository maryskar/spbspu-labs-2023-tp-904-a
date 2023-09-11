#include "command_executor.h"
#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>

namespace kumachev {
  using dict_map_pair = std::pair< const std::string, er_dictionary >;

  static std::string getDictName(const dict_map_pair &pair)
  {
    return pair.first;
  }

  static void handleHelp(State &state, string_vector &args,
      std::ostream &ostream);

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

  static void handleTranslate(State &state, string_vector &args,
      std::ostream &ostream);

  static void handleExecute(State &state, string_vector &args,
      std::ostream &ostream);

  static void handleMerge(State &state, string_vector &args,
      std::ostream &ostream);

  static void handleSubtract(State &state, string_vector &args,
      std::ostream &ostream);

  CommandExecutor::CommandExecutor(std::istream &istream, std::ostream &ostream,
    const CommandSystem &commandSystem, State &state, bool interactive):
    istream_(istream),
    ostream_(ostream),
    commandSystem_(commandSystem),
    interactive_(interactive),
    state_(state)
  {
  }

  void CommandExecutor::handleCommand()
  {
    std::string line, command;

    std::getline(istream_, line, '\n');
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
      throw std::logic_error("Command not found");
    }
  }

  CommandSystem createCommandSystem()
  {
    CommandSystem commandSystem;
    commandSystem.handlers["help"] = handleHelp;
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

  void handleHelp(State &state, string_vector &args, std::ostream &ostream)
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
            << "словарь <dict2> из <dict1 и записать"
            << " результат в <dict_out>\n\n";
  }

  void handleDicts(State &state, string_vector &args, std::ostream &ostream)
  {
    if (!args.empty()) {
      throw std::logic_error("Команда не принимает аргументы");
    }

    if (state.dicts.empty()) {
      ostream << "<пусто>\n";
    }

    std::vector< std::string > names;
    names.reserve(state.dicts.size());
    auto inserter = std::back_inserter(names);
    const auto& dicts = state.dicts;
    std::transform(dicts.cbegin(), dicts.cend(), inserter, getDictName);

    auto output = std::ostream_iterator<std::string>(ostream, "\n");
    std::copy(names.cbegin(), names.cend(), output);
  }

  void handleCreate(State &state, string_vector &args, std::ostream &ostream)
  {
    if (args.size() != 1) {
      throw std::logic_error("Команда принимает 1 аргумент");
    }

    std::string dictName = args[0];

    if (state.dicts.find(dictName) == state.dicts.end()) {
      state.dicts[dictName] = er_dictionary();
    } else {
      throw std::logic_error("ОШИБКА: Словарь с таким именем уже существует");
    }
  }

  void handleLoad(State &state, string_vector &args, std::ostream &ostream)
  {

  }

  void handleSave(State &state, string_vector &args, std::ostream &ostream)
  {

  }

  void handleAdd(State &state, string_vector &args, std::ostream &ostream)
  {
    if (args.size() < 3) {
      throw std::logic_error("Команда принимает минимум 3 аргумента");
    }

    std::string dictName = args[0];
    std::string english = args[1];
    auto russianBegin = args.cbegin();
    std::advance(russianBegin, 2);

    std::vector< std::string > russianWords(russianBegin, args.cend());
    const auto &searchResult = state.dicts.find(dictName);

    if (searchResult == state.dicts.end()) {
      throw std::logic_error("ОШИБКА: Словарь не найден");
    }

    searchResult->second[english] = russianWords;
  }

  void handleClear(State &state, string_vector &args, std::ostream &ostream)
  {

  }

  void handleTranslate(State &state, string_vector &args, std::ostream &ostream)
  {

  }

  void handleExecute(State &state, string_vector &args, std::ostream &ostream)
  {

  }

  void handleMerge(State &state, string_vector &args, std::ostream &ostream)
  {

  }

  void handleSubtract(State &state, string_vector &args, std::ostream &ostream)
  {

  }
}
