#include "commandsImpl.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "commands.h"
std::vector< std::string > history;
void addHistory(const std::string &command)
{
  history.push_back(command);
}

void showHistory(std::ostream &out)
{
size_t count = 0;
for (const std::string &command : history)
{
out << count << ") " << command << "\n";
++count;
}
}
dictOfTranslations createDictOftranslations(std::istream &in)
{
  std::string word = "";
  in >> word;
  addHistory(word);
  dictOfTranslations dict;
  std::vector<std::string> translations;
  while (in)
  {
    std::string translation = "";
    in >> translation;
    addHistory(word);
    if (translation == ";" || translation == ".")
    {
      break;
    }
    translations.push_back(translation);
    dict[word] = translations;
  }
  return dict;
}

void createDict(std::istream &in, dictOfDicts &dict)
{
  while (in)
  {
    std::string name = "";
    in >> name;
    addHistory(name);
    if (name == "stop")
    {
      break; // Выход из цикла createDict при вводе "stop"
    }
    dictOfTranslations translations = createDictOftranslations(in);
    dict[name] = translations;
  }
}

void outDictionaries(const dictOfDicts &dicts, std::ostream &out)
{
  for (const auto &entry : dicts)
  {
    out << "Dictionary: " << entry.first << "\n";
    const dictOfTranslations &dictionary = entry.second;

    for (const auto &word_entry : dictionary)
    {
      out << "  Word: " << word_entry.first << "\n";
      out << "  Translations: ";
      const std::vector<std::string> &translations = word_entry.second;

      for (const std::string &translation : translations)
      {
        out << translation << " ";
      }
      out << "\n";
    }
    out << "\n";
  }
}

void translate(std::istream &in, dictOfDicts &dicts, std::ostream &out)
{
  while (in)
  {
    std::string nameOfDict = "";
    in >> nameOfDict;
    addHistory(nameOfDict);
    if (nameOfDict == "stop")
    {
      return;
    }
    std::string word = "";
    while (in)
    {
      in >> word;
      addHistory(word);
      if (word == "." || word == ";")
      {
        break;
      }
      auto dictIter = dicts.find(nameOfDict);
      if (dictIter == dicts.end())
      {
        out << "Dictionary '" << nameOfDict << "' not found." << std::endl;
        return;
      }
      const dictOfTranslations &dictionary = dictIter->second;
      auto translationIter = dictionary.find(word);
      if (translationIter != dictionary.end())
      {
        const std::vector< std::string > translations = translationIter->second;
        out << word << " translations in dictionary " << nameOfDict << ":" << "\n";
        for (const std::string &translation : translations)
        {
          out << "- " << translation << "\n";
        }
      }
      else
      {
        out << "word not found";
      }
    }
  }
}

void help(std::ostream &out)
{
  out << "Commands that you are able to use:" << "\n";
  out << "1) CREATE - creates new dictionary" << "\n";
  out << "example : CREATE eng1 hello привет здравствуйте ; eng2 car машина автомобиль" << "\n";
  out << "2) OUT - creates a list of dictionaries in console" << "\n";
  out << "3) HISTORY - shows previous commands" << "\n";
  out << "4) TRANSLATE - shows a translation/translations of a word" << "\n";
  out << "5) INTERSECTION - create a new dict with intersection of dictionaries, which names you have inserted" << "\n";
  out << "6) INION - unite dictionaries, which names you have inserted and create new dictionary" << "\n";
  out << "7) HELP" << "\n";
}

void doIntersect(std::istream &in, dictOfDicts &dicts, std::ostream &out)
{
  std::string newNameOfDict;
  in >> newNameOfDict;
  addHistory(newNameOfDict);
  dictOfTranslations intersectedDict;

  while (true)
  {
    std::string dictName;
    in >> dictName;
    addHistory(dictName);
    if (dictName == "stop")
    {
      break;
    }

    auto dictIter = dicts.find(dictName);
    if (dictIter != dicts.end())
    {
      const dictOfTranslations &dictionary = dictIter->second;

      for (const auto &word_entry : dictionary)
      {
        const std::string &word = word_entry.first;
        const std::vector<std::string> &translations = word_entry.second;

        if (intersectedDict.find(word) == intersectedDict.end())
        {
          intersectedDict[word] = translations;
        }
        else
        {
          std::vector<std::string> &existingTranslations = intersectedDict[word];
          for (const std::string &translation : translations)
          {
            if (std::find(existingTranslations.begin(), existingTranslations.end(), translation) == existingTranslations.end())
            {
              existingTranslations.push_back(translation);
            }
          }
        }
      }
    }
    else
    {
      out << "Dictionary '" << dictName << "' not found." << std::endl;
    }
  }
  dicts[newNameOfDict] = intersectedDict;

  out << "New dictionary '" << newNameOfDict << "' created with intersection of dictionaries." << std::endl;
}

void unite(std::istream &in, dictOfDicts &dicts, std::ostream &out)
{
  std::string newNameOfDict;
  in >> newNameOfDict;
  addHistory(newNameOfDict);
  dictOfTranslations unionDict;

  while (true)
  {
    std::string dictName;
    in >> dictName;
    addHistory(dictName);
    if (dictName == "stop")
    {
      break;
    }

    auto dictIter = dicts.find(dictName);
    if (dictIter != dicts.end())
    {
      const dictOfTranslations &dictionary = dictIter->second;

      for (const auto &word_entry : dictionary)
      {
        const std::string &word = word_entry.first;
        const std::vector<std::string> &translations = word_entry.second;
        unionDict[word] = translations;
      }
    }
    else
    {
      out << "Dictionary '" << dictName << "' not found." << std::endl;
    }
  }
  dicts[newNameOfDict] = unionDict;

  out << "New dictionary '" << newNameOfDict << "' created with union of dictionaries." << std::endl;
}



