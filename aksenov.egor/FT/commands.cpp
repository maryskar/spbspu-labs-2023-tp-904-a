#include "commands.h"
#include <limits>
#include <algorithm>
#include <stdexcept>
#include "helpFunctions.h"
std::string insertCommand(std::istream &in)
{
  std::string command = "";
  in >> command;
  if (!in)
  {
    throw std::runtime_error("stream is over");
  }
  return command;
}
Commands::Commands()
{
  dict1_.insert({"help", help});
  dict2_.insert({"createDictionary", createDictionary});
  dict3_.insert({"outDictionaries", outDictionaries});
  dict4_.insert({"translate", translate});
  //dict5_.insert({"doIntersect", doIntersect});
}
void Commands::doCommand(const std::string &command, const std::string &str, dictOfDicts &dicts, std::ostream &out) const
{
  auto func = dict4_.at(command);
  func(str, dicts, out);
}
void Commands::doCommand(const std::string &command, std::ostream &out) const
{
  auto func = dict1_.at(command);
  func(out);
}
void Commands::doCommand(const std::string &command, std::istream &in, dictOfDicts &dict) const
{
  auto func = dict2_.at(command);
  func(in, dict);
}
void Commands::doCommand(const std::string &command, dictOfDicts &dicts, std::ostream &out) const
{
  auto func = dict3_.at(command);
  func(dicts, out);
}

void Commands::doCommand(const std::string &command, const std::string &str, dictOfDicts &dicts) const
{
  auto func = dict5_.at(command);
  func(str, dicts);
}
void help(std::ostream &out)
{
  out << "Commands that you are able to use:" << "\n";
  out << "1) newDictionary - creates new dictionary" << "\n";
  out << "2) outDictionaries - creates a list of dictionaries in console" << "\n";
  out << "3) history - shows previous commands" << "\n";
  out << "4) translate - shows a translation/translations of a word" << "\n";
  out << "5) intersection - makes new dictionary, which contains the intersection of dictionaries" << "\n";
  out << "6) unite - make new dictionary from unic elements of dictionaries" << "\n";
  out << "7) filter - shows all the words, start with a letter" << "\n";
  out << "8) switch language - switch a native language of dictionary" << "\n";
}

/*void createDictionary(std::istream &in, dict_t &dict)
{
  std::string line;
  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  while (true)
  {
    std::getline(std::cin, line);
    if (line == "stop")
    {
      break;
    }

    if (!line.empty())
    {
      size_t space_index = line.find_first_of(' ');
      if (space_index != std::string::npos)
      {
        en_word_t en = line.substr(0, space_index);
        std::string ru_list_str = line.substr(space_index + 1);

        dict[en] = splitStringToTranslation(ru_list_str);
      }
    }
  }
}*/
void createDictionary(std::istream &in, dictOfDicts &dicts)
{
  std::string dictName;
  while (true)
  {
    std::cout << "Insert a name of the dictionary (or 'stop' to finish): ";
    std::getline(std::cin, dictName);

    if (dictName == "stop")
    {
      break;
    }

    // Check if the dictionary name is not empty
    if (!dictName.empty())
    {
      dict_t dictionary; // Create a new dictionary for this entry
      std::string line;

      while (true)
      {
        std::cout << "Insert a word and its translations (or 'done' to finish): ";
        std::getline(std::cin, line);

        if (line == "done")
        {
          break;
        }

        size_t space_index = line.find_first_of(' ');
        if (space_index != std::string::npos)
        {
          en_word_t word = line.substr(0, space_index);
          std::string ru_list_str = line.substr(space_index + 1);

          dictionary[word] = splitStringToTranslation(ru_list_str);
        }
      }

      // Add this dictionary to the dictOfDicts
      dicts[dictName] = dictionary;
    }
  }
  std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}
/*void outDictionaries(dictOfDicts dicts, std::ostream &out)
{
  for (const auto& entry : dicts)
  {
    out << "dict: " << entry.first << "\n";
    outDict(entry.second, out, ",");
  }
}*/

void outDictionaries(const dictOfDicts &dicts, std::ostream &out)
{
  for (const auto &entry : dicts)
  {
    out << "Dictionary: " << entry.first << "\n";
    const dict_t &dictionary = entry.second;

    for (const auto &word_entry : dictionary)
    {
      out << "  Word: " << word_entry.first << "\n";
      out << "  Translations: ";
      const ru_vector_t &translations = word_entry.second;

      for (const std::string &translation : translations)
      {
        out << translation << " ";
      }
      out << "\n";
    }
    out << "\n";
  }
}

/*void translate(const std::string &str, dictOfDicts &dicts, std::ostream &out)
{
  std::vector< std::string > names = getNamesFromString(str);
  if (names.size() != 2)
  {
    throw std::invalid_argument("Bad number of args!");
  }

  if (isValidDict(names.at(0), dicts))
  {
    const dict_t& dict = dicts[names.at(0)];
    std::string english_word = names.at(1);

    auto translation_iter = dict.find(english_word);
    if (translation_iter == dict.end())
    {
      out << "None" << "\n";
    }
    else
    {
      out << english_word << ' ';
      outRuList(translation_iter->second, out, " ");
    }
  }
  else
  {
    throw std::logic_error("Bad args!");
  }
}*/

void translate(const std::string& input, dictOfDicts &dicts, std::ostream &out)
{
  // Разбиваем входную строку на две части: название словаря и слово для перевода
  size_t space_index = input.find_first_of(' ');
  if (space_index == std::string::npos)
  {
    out << "Invalid input format. Please provide a dictionary name and a word to translate." << std::endl;
    return;
  }

  std::string dictionary_name = input.substr(0, space_index);
  std::string word_to_translate = input.substr(space_index + 1);

  // Проверяем, существует ли указанный словарь
  auto dict_iter = dicts.find(dictionary_name);
  if (dict_iter == dicts.end())
  {
    out << "Dictionary '" << dictionary_name << "' not found." << std::endl;
    return;
  }

  // Ищем перевод слова в указанном словаре
  const dict_t& dictionary = dict_iter->second;
  auto translation_iter = dictionary.find(word_to_translate);

  if (translation_iter != dictionary.end())
  {
    const ru_vector_t& translations = translation_iter->second;
    out << word_to_translate << " translations in dictionary '" << dictionary_name << "':" << std::endl;

    for (const std::string& translation : translations)
    {
      out << "- " << translation << std::endl;
    }
  }
  else
  {
    out << "Word '" << word_to_translate << "' not found in dictionary '" << dictionary_name << "'." << std::endl;
  }
}

void doIntersect(const std::string& dictName1, const std::string& dictName2, dictOfDicts & dicts)
{
  if (!isValidDict(dictName1, dicts) || !isValidDict(dictName2, dicts))
  {
    throw std::invalid_argument("Invalid dictionary names!");
  }

  const dict_t& dict1 = dicts[dictName1];
  const dict_t& dict2 = dicts[dictName2];
  dict_t intersection;

  for (const auto& entry : dict1)
  {
    const en_word_t& word = entry.first;
    const ru_vector_t& translations = entry.second;

    // Check if the word is also present in the second dictionary
    if (dict2.find(word) != dict2.end())
    {
      // If yes, add the word and its translations to the intersection dictionary
      intersection[word] = translations;
    }
  }

  // Add the intersection dictionary with a new name
  std::string newDictName = dictName1 + "_intersect_" + dictName2;
  dicts[newDictName] = intersection;
}

void executeCommand(std::ostream &out, std::istream &in, Commands &commands, dictOfDicts &dicts, dict_t &dict, std::string command, std::string &line)
{
  try
  {
    if (command == "help")
    {
      commands.doCommand(command, out);
    }
    else if (command == "createDictionary")
    {
      commands.doCommand(command, in, dicts);
    }
    else if (command == "outDictionaries")
    {
      commands.doCommand(command, dicts, out);
    }
    else if (command == "translate")
    {
      commands.doCommand(command, line , dicts, out);
    }
    /*else if (command == "doIntersect")
    {
      commands.doCommand(command, str, dicts);
    }*/
    else
    {
      out << "Unknown command." << std::endl;
    }
  }
  catch (const std::out_of_range &e)
  {
    out << "Command not found." << std::endl;
  }
}