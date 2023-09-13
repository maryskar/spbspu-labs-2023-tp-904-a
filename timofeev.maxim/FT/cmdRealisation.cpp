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
    }
    else if (tmp == "List")
    {
      out << "[AddWord Rus, " << "AddWord Eng, " << "Exist, " << "Delete All, " << "\n";
      out << "Delete Eng, " << "Delete Rus, " << "DeleteT Rus, " << "DeleteT Eng, " << "\n";
      out << "Print All, " << "Print Eng, " << "Print Rus, " << "\n";
      out << "Translate Rus, " << "Translate Eng]" << "\n";
    }
    else
    {
      throw std::logic_error("Wrong Command");
    }
  }

  void AddWord(std::istream& in, std::ostream&, dictsOfDicts & dicts)
  {
    std::string secPart = "";
    in >> secPart;
    if (secPart == "Rus")
    {
      dict& rusDict = dicts["Ru"];
      readDict(in, rusDict);
    }
    else if (secPart == "Eng")
    {
      dict& engDict = dicts["Eng"];
      readDict(in, engDict);
    }
    else
    {
      throw std::logic_error("Wrong Command");
    }
  }

  void DeleteT(std::istream& in, std::ostream&, dictsOfDicts & dicts)
  {
    std::string secPart = "";
    in >> secPart;
    if (secPart == "Rus")
    {
      dict& rusDict = dicts["Ru"];
      delTrans(in, rusDict);
    }
    else if (secPart == "Eng")
    {
      dict& engDict = dicts["Eng"];
      delTrans(in, engDict);
    }
    else
    {
      throw std::logic_error("Wrong Command");
    }
  }

  void Print(std::istream& in, std::ostream& out, dictsOfDicts & dicts)
  {
    std::string secPart = "";
    in >> secPart;
    if (secPart == "Rus")
    {
      dict& rusDict = dicts["Ru"];
      printDict(out, rusDict);
    }
    else if (secPart == "Eng")
    {
      dict& engDict = dicts["Eng"];
      printDict(out, engDict);
    }
    else if (secPart == "All")
    {
      dict& rusDict = dicts["Ru"];
      dict& engDict = dicts["Eng"];
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
}