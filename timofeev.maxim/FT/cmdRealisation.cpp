#include "cmdRealisation.h"
#include <vector>
#include <map>
#include <unordered_set>
#include "HelpFunction.h"
namespace timofeev
{
  void doCreateDict(std::istream& in, std::ostream&, dictsOfDicts& dicts)
  {
    std::string Name;
    std::getline(in, Name);
    std::map < std::string, std::vector< std::string > > translateDict;
    size_t start;
    size_t end = 0;
    while ((start = Name.find_first_not_of(' ', end)) != std::string::npos)
    {
      end = Name.find(' ', start);
      std::string tmp;
      tmp = Name.substr(start, end - start);
      dicts[tmp] = translateDict;
    }

  }
  void doPrintHelp(std::istream& in, std::ostream& out, dictsOfDicts &)
  {
    out << "Select which command you need: " << "\n";
    out << "Write down \"All\" to get full info: " << "\n";
    out << "Write down \"List\" to get list of command: " << "\n";
    std::string tmp = "";
    in >> tmp;
    if (tmp == "All")
    {
      out << "Create \"name\" - let you make new dictionary and use it\n";
      out << "AddWord \"name\" - let you add word and translation chosen dictionary \n";
      out << "Exist - a command that will help you find out if a word is in a any dictionary ";
      out << "and in which one it is\n";
      out << "Delete All - delete all dictionaries\n";
      out << "Delete \"name\" - delete chosen dictionary\n";
      out << "DeleteT \"name\" - delete translation in chosen dictionary\n";
      out << "Print All - print all dictionaries\n";
      out << "Print \"name\" - print chosen dictionary\n";
      out << "Translate \"name\" - show you translation of word in chosen dictionary\n";
      out << "Common - show you common words in dictionaries\n";
    }
    else if (tmp == "List")
    {
      out << "[AddWord \"name\", "  << "Exist, " << "Delete All, " << "\n";
      out << "Delete \"name\", " << "DeleteT \"name\", " << "\n";
      out << "Print All, " << "Print \"name\", " << "\n";
      out << "Translate \"name\", " << "Common, " << "DictList]" << "\n";
    }
    else
    {
      throw std::logic_error("Wrong Command");
    }
  }

  void doAddWord(std::istream& in, std::ostream& out, dictsOfDicts& dicts)
  {
    std::string secPart = "";
    in >> secPart;
    try
    {
      dict& lilDict = dicts[secPart];
      addInDict(in, out, lilDict);
    }
    catch (...)
    {
      throw std::logic_error("Wrong Command");
    }
  }

  void doDeleteT(std::istream& in, std::ostream& out, dictsOfDicts& dicts)
  {
    std::string secPart = "";
    in >> secPart;
    try
    {
      dict& dictionary = dicts[secPart];
      delTrans(in, out, dictionary);
    }
    catch(...)
    {
      throw std::logic_error("Wrong Command");
    }
  }

  void doPrint(std::istream& in, std::ostream& out, dictsOfDicts& dicts)
  {
    std::string secPart = "";
    in >> secPart;
    try
    {
      if (secPart == "All")
      {
        for (auto p: dicts)
        {
          printDict(out, p.second);
        }
      }
      else
      {
        dict& dictionary = dicts[secPart];
        printDict(out, dictionary);
      }
    }
    catch (...)
    {
      throw std::logic_error("Wrong Command");
    }
  }

  void doDelete(std::istream& in, std::ostream&, dictsOfDicts& dicts)
  {
    std::string secPart = "";
    in >> secPart;
    try
    {
      if (secPart == "All")
      {
        for (auto p: dicts)
        {
          delDict(p.second);
        }
      }
      else
      {
        dict& dictionary = dicts[secPart];
        delDict(dictionary);;
      }
    }
    catch (...)
    {
      throw std::logic_error("Wrong Command");
    }
  }

  void doTranslate(std::istream& in, std::ostream& out, dictsOfDicts& dicts)
  {
    std::string secPart = "";
    std::string word = "";
    in >> secPart;
    try
    {
      in >> word;
      dict& dictionary = dicts[secPart];
      findTrans(out, word, dictionary);
    }
    catch (...)
    {
      throw std::logic_error("Wrong Command");
    }
  }
  void doExist(std::istream& in, std::ostream& out, dictsOfDicts& dicts)
  {
    std::string word;
    in >> word;
    bool flag = false;
    try
    {
      if (dicts.empty())
      {
        out << "No dictionaries" << "\n";
        return;
      }
      for (auto p: dicts)
      {
        if (findWord(word, p.second))
        {
          out << word << " in " << p.first << "\n";
          flag = true;
        }
      }
      if (!flag)
      {
        out << "No matches" << "\n";
      }
    }
    catch (...)
    {
      throw std::logic_error("Wrong Command");
    }
  }

  void doCommon(std::istream&, std::ostream& out, dictsOfDicts& dicts)
  {
    std::unordered_set< std::string > unique;
    for (const auto& names: dicts)
    {
      const std::map< std::string, std::vector< std::string > >& dict = names.second;
      for (const auto& word: dict)
      {
        const std::vector< std::string >& wordList = word.second;
        for (const std::string& translation: wordList)
        {
          if (unique.count(word.first) > 0 || unique.count(translation) > 0)
          {
            out << word.first << "-" << translation << "\n";
          }
          else
          {
            unique.insert(word.first);
            unique.insert(translation);
          }
        }
      }
    }
  }
}
