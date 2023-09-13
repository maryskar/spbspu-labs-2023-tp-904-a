#include "cmdRealisation.h"
#include "HelpFunction.h"
namespace timofeev
{
  void printHelp(std::istream& in, std::ostream& out, dictsOfDicts &)
  {
    out << "Select which command you need:" << "\n";
    out << "Write down \"All\" to get full info:" << "\n";
    out << "Write down \"List\" to get list of command:" << "\n";
    std::string tmp = "";
    in >> tmp;
    if (tmp == "All")
    {
      out << "AddWord Rus - let you add word in Russian with English translation (rus + eng)\n";
      out << "AddWord Eng - let you add word in English with Russian translation (eng + rus)\n";
      out << "Exist - a command that will help you find out if a word is in a any dictionary ";
      out << "and in which one it is\n";
      out << "Delete All - delete all dictionaries\n";
      out << "Delete Eng - delete English dictionary\n";
      out << "Delete Rus - delete Russian dictionary\n";
      out << "DeleteT Rus - delete English translation in Russian dictionary\n";
      out << "DeleteT Eng - delete Russian translation in English dictionary\n";
      out << "Print All - print all dictionaries\n";
      out << "Print Eng - print English dictionary\n";
      out << "Print Rus - print Russian dictionary\n";
      out << "Translate Eng - show you translation of English word in Russian\n";
      out << "Translate Rus - show you translation of Russian word in English\n";
      out << "Common - show you common words in dictionaries\n";
    }
    else if (tmp == "List")
    {
      out << "[AddWord Rus, " << "AddWord Eng, " << "Exist, " << "Delete All, " << "\n";
      out << "Delete Eng, " << "Delete Rus, " << "DeleteT Rus, " << "DeleteT Eng, " << "\n";
      out << "Print All, " << "Print Eng, " << "Print Rus, " << "\n";
      out << "Translate Rus, " << "Translate Eng, " << "Common]" << "\n";
    }
    else
    {
      throw std::logic_error("Wrong Command");
    }
  }

  void AddWord(std::istream& in, std::ostream& out, dictsOfDicts& dicts)
  {
    std::string secPart = "";
    in >> secPart;
    if (secPart == "Rus")
    {
      dict& rusDict = dicts["Ru"];
      readDict(in, out, rusDict);
    }
    else if (secPart == "Eng")
    {
      dict& engDict = dicts["Eng"];
      readDict(in, out, engDict);
    }
    else
    {
      throw std::logic_error("Wrong Command");
    }
  }

  void DeleteT(std::istream& in, std::ostream& out, dictsOfDicts& dicts)
  {
    std::string secPart = "";
    in >> secPart;
    if (secPart == "Rus")
    {
      dict& rusDict = dicts["Ru"];
      delTrans(in, out, rusDict);
    }
    else if (secPart == "Eng")
    {
      dict& engDict = dicts["Eng"];
      delTrans(in, out, engDict);
    }
    else
    {
      throw std::logic_error("Wrong Command");
    }
  }

  void Print(std::istream& in, std::ostream& out, dictsOfDicts& dicts)
  {
    std::string secPart = "";
    in >> secPart;
    dict& rusDict = dicts["Ru"];
    dict& engDict = dicts["Eng"];
    if (secPart == "Rus")
    {
      printDict(out, rusDict);
    }
    else if (secPart == "Eng")
    {
      printDict(out, engDict);
    }
    else if (secPart == "All")
    {
      out << "Russian dictionary:" << "\n";
      printDict(out, rusDict);
      out << "English dictionary:" << "\n";
      printDict(out, engDict);
    }
    else
    {
      throw std::logic_error("Wrong Command");
    }
  }

  void Delete(std::istream& in, std::ostream& out, dictsOfDicts& dicts)
  {
    std::string secPart = "";
    in >> secPart;
    dict& rusDict = dicts["Ru"];
    dict& engDict = dicts["Eng"];
    if (secPart == "Rus")
    {
      delDict(rusDict);
      out << "Done!" << "\n";
    }
    else if (secPart == "Eng")
    {
      delDict(engDict);
      out << "Done!" << "\n";
    }
    else if (secPart == "All")
    {
      delDict(rusDict);
      delDict(engDict);
      out << "Done!" << "\n";
    }
    else
    {
      throw std::logic_error("Wrong Command");
    }
  }

  void Translate(std::istream& in, std::ostream& out, dictsOfDicts& dicts)
  {
    std::string secPart = "";
    std::string word = "";
    in >> secPart;
    if (secPart == "Rus")
    {
      in >> word;
      dict& rusDict = dicts["Ru"];
      findTrans(out, word, rusDict);
    }
    else if (secPart == "Eng")
    {
      in >> word;
      dict& engDict = dicts["Eng"];
      findTrans(out, word, engDict);
    }
  }
  void Exist(std::istream& in, std::ostream& out, dictsOfDicts& dicts)
  {
    std::string word;
    in >> word;
    dict& rusDict = dicts["Ru"];
    dict& engDict = dicts["Eng"];
    if (findWord(word, rusDict) && findWord(word, engDict))
    {
      out << word << " In both Dicts";
    }
    else if (findWord(word, engDict))
    {
      out << word << " In English Dict";
    }
    else if (findWord(word, rusDict))
    {
      out << word << " In Russian Dict";
    }
    else
    {
      out << "No matches";
    }
  }

  void Common(std::istream&, std::ostream& out, dictsOfDicts& dicts)
  {
    dict& rusDict = dicts["Ru"];
    dict& engDict = dicts["Eng"];
    size_t count = 0;
    for (const auto &i: rusDict)
    {
      for (const auto &y: engDict)
      {
        for (const std::string &word: i.second)
        {
          for (const std::string &tmp: y.second)
          {
            if (i.first == tmp && y.first == word)
            {
              out << i.first << " " << y.first << "\n";
              count++;
            }
          }
        }
      }
    }
    if (count == 0)
    {
      out << "No matching";
    }
  }
}
